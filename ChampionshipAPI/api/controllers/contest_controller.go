package controllers

import (
	"ChampionshipAPI/api/database"
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/repository"
	"ChampionshipAPI/api/repository/crud"
	"ChampionshipAPI/api/responses"
	"ChampionshipAPI/api/utils/random"
	"encoding/json"
	"errors"
	"fmt"
	"net/http"
)

// GetContests from the DB
func GetContests(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)

	func(contestRepo repository.ContestRepository) {
		contests, err := contestRepo.FindAll()
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}

		responses.JSON(w, http.StatusOK, contests)
	}(repo)
}

// GetContestsByRange from DB
func GetContestsByRange(w http.ResponseWriter, r *http.Request) {
	startID, err := VarsUint("id", r)
	if err != nil || startID <= 0 {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	count, err := VarsUint("value", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)

	func(contestRepo repository.ContestRepository) {
		contests, err := contestRepo.FindAllByRange(uint32(startID), uint32(startID+count-1))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, contests)
	}(repo)

}

// GetContest from DB
func GetContest(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)

	func(contestRepo repository.ContestRepository) {
		contest, err := contestRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, contest)
	}(repo)

}

// CountContests value from DB
func CountContests(w http.ResponseWriter, r *http.Request) {
	fmt.Println("count")
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)

	func(contestRepo repository.ContestRepository) {
		contests, err := contestRepo.Count()
		println(contests)
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, contests)
	}(repo)
}

// CountMemberTypesInContest : get number of member types in the specified contest from DB
// CountMemberTypesInContest : получает количество типов учатников для указанного соревнования
func CountMemberTypesInContest(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)
	func(contestRepo repository.ContestRepository) {
		contests, err := contestRepo.CountMemberTypes(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, contests)
	}(repo)
}

func GetMemberTypesForContest(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryContestCRUD(db)

	func(contestRepo repository.ContestRepository) {
		contest, err := contestRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, contest.MemberType)
	}(repo)
}

func CountOfMembersForContest(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repoContest := crud.NewRepositoryContestCRUD(db)

	// get member types slice for contest
	var memberTypesForContest []models.TypeMember
	func(contestRepo repository.ContestRepository) {
		contest, err := contestRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		memberTypesForContest = append(memberTypesForContest, contest.MemberType...)
	}(repoContest)

	repoMemberTypes := crud.NewRepositoryTypeMemberCRUD(db)

	var countMember uint64
	func(memberTypesRepo repository.MemberTypeRepository) {
		for _, val := range memberTypesForContest {
			count, err := memberTypesRepo.CountMembers(uint32(val.ID))
			if err != nil {
				responses.ERROR(w, http.StatusBadRequest, err)
				return
			}
			countMember = countMember + uint64(count)
		}
		
		responses.JSON(w, http.StatusOK, countMember)
	}(repoMemberTypes)
}

func GetRandomMembersForContest(w http.ResponseWriter, r *http.Request) {
	type randomMemberRequest struct {
		Count uint32 `json:"count"`
	}

	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	// from json to memberReq
	memberReq := randomMemberRequest{}
	err = json.NewDecoder(r.Body).Decode(&memberReq)
	if err != nil || memberReq.Count == 0 {
		responses.ERROR(w, http.StatusUnprocessableEntity, err)
		return
	}

	// database connect
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	contestRepo := crud.NewRepositoryContestCRUD(db)
	memberTypes := []models.TypeMember{}
	func(repo repository.ContestRepository) {
		contest, err := repo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		memberTypes = append(memberTypes, contest.MemberType...)
	}(contestRepo)

	memberTypesRepo := crud.NewRepositoryTypeMemberCRUD(db)

	func(typeRepo repository.MemberTypeRepository) {
		var membersID []uint64
		members := make(map[uint64]models.Member)

		for _, val := range memberTypes {
			// get info about every member type from db
			// получение информации о каждом типе учатников из бд
			row, err := typeRepo.FindByID(uint32(val.ID))
			if err != nil {
				responses.ERROR(w, http.StatusBadRequest, err)
				return
			}

			// fill members id slice and members map
			// заполнение слайса айди участников и мапы участников
			for _, mem := range row.Member {
				membersID = append(membersID, mem.ID)
				members[mem.ID] = mem
			}
		}

		// shuffling members id slice
		// перемешивание слайса айди участников
		random.ShuffleUint64(&membersID)

		if uint32(len(members)) < memberReq.Count {
			responses.ERROR(w, http.StatusUnprocessableEntity,
				errors.New("the requested quantity is greater than the actual quantity"))
			return
		}

		sendRandomMembers(memberReq.Count, &members, &membersID, w)

	}(memberTypesRepo)
}

func CreateContest(w http.ResponseWriter, r *http.Request) {
	//
}

func UpdateContest(w http.ResponseWriter, r *http.Request) {
	//
}

func DeleteContest(w http.ResponseWriter, r *http.Request) {
	//
}
