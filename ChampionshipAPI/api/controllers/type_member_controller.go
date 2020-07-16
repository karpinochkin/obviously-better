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
	"net/http"
)

// GetMemberTypes from the DB
func GetMemberTypes(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryTypeMemberCRUD(db)
	func(typeMemberRepo repository.MemberTypeRepository) {
		memberTypes, err := typeMemberRepo.FindAll()
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}
		responses.JSON(w, http.StatusOK, memberTypes)
	}(repo)
}

// GetMemberType from DB
func GetMemberType(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryTypeMemberCRUD(db)

	func(typeMemberRepo repository.MemberTypeRepository) {
		typeMember, err := typeMemberRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, typeMember)
	}(repo)
}

// CountMemberTypes from the DB
func CountMemberTypes(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryTypeMemberCRUD(db)

	func(typeMemberRepo repository.MemberTypeRepository) {
		typeMember, err := typeMemberRepo.Count()
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, typeMember)
	}(repo)
}

// CountMembersInMemberType send number of members in the specified member type
// CountMembersInMemberType отправляет клиенту количество участников в указанном типе участников
func CountMembersInMemberType(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryTypeMemberCRUD(db)

	func(typeMemberRepo repository.MemberTypeRepository) {
		typeMember, err := typeMemberRepo.CountMembers(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, typeMember)
	}(repo)
}

// GetRandomMembersForMemberTypes sends a random slice of members from the specified members types and their count
// GetRandomMembersForMemberTypes отправляет случайный срез учатников из указанных типов участников и их количества
func GetRandomMembersForMemberTypes(w http.ResponseWriter, r *http.Request) {
	type randomMemberRequest struct {
		Count         uint32   `json:"count"`
		MemberTypesID []uint32 `json:"member_types_id"`
	}

	// from json to memberReq
	memberReq := randomMemberRequest{}
	err := json.NewDecoder(r.Body).Decode(&memberReq)
	if err != nil || memberReq.Count == 0 || len(memberReq.MemberTypesID) == 0 {
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

	repo := crud.NewRepositoryTypeMemberCRUD(db)

	func(typeRepo repository.MemberTypeRepository) {
		var membersID []uint64
		members := make(map[uint64]models.Member)

		for _, val := range memberReq.MemberTypesID {
			// get info about every member type from db
			// получение информации о каждом типе учатников из бд
			row, err := typeRepo.FindByID(val)
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

	}(repo)
}

func sendRandomMembers(count uint32, members *map[uint64]models.Member, membersID *[]uint64, w http.ResponseWriter) {
	var err error
	var output []models.MemberWithoutImage
	var i uint32 = 0
	// fill output slice until the values in this slice are less than the desired number
	// заполнение выходного слайса пока значений в нем меньше, чем требуется
	for i < count {
		mem, ok := (*members)[(*membersID)[i]]
		if !ok {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}

		output = append(output, models.MemberWithoutImage{ID: mem.ID, Name: mem.Name, Description: mem.Description})
		i++
	}
	responses.JSON(w, http.StatusOK, output)
}

// CreateMemberType from the DB
func CreateMemberType(w http.ResponseWriter, r *http.Request) {
	//////////////////////////////////////////////////////////
}

// UpdateMemberType from DB
func UpdateMemberType(w http.ResponseWriter, r *http.Request) {
	//////////////////////////////////////////////////////////
}

// DeleteMemberType from DB
func DeleteMemberType(w http.ResponseWriter, r *http.Request) {
	//////////////////////////////////////////////////////////
}
