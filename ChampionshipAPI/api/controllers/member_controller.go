package controllers

import (
	"ChampionshipAPI/api/database"
	"ChampionshipAPI/api/repository"
	"ChampionshipAPI/api/repository/crud"
	"ChampionshipAPI/api/responses"
	"net/http"
)

// GetMembers from the DB
func GetMembers(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryMemberCRUD(db)

	func(memberRepo repository.MemberRepository) {
		members, err := memberRepo.FindAll()
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}
		responses.JSON(w, http.StatusOK, members)
	}(repo)

}

// GetMember from DB
func GetMember(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryMemberCRUD(db)

	func(memberRepo repository.MemberRepository) {
		member, err := memberRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, member)
	}(repo)
}

// GetMemberImage : sends image by id
func GetMemberImage(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryMemberCRUD(db)

	func(memberRepo repository.MemberRepository) {
		member, err := memberRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, member.Image)
		// responses.JSON(w, http.StatusOK, member)
	}(repo)
}

func CreateMember(w http.ResponseWriter, r *http.Request) {
	//
}

func UpdateMember(w http.ResponseWriter, r *http.Request) {
	//
}

func DeleteMember(w http.ResponseWriter, r *http.Request) {
	//
}
