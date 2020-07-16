package controllers

import (
	"ChampionshipAPI/api/database"
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/repository"
	"ChampionshipAPI/api/repository/crud"
	"ChampionshipAPI/api/responses"
	"encoding/json"
	"fmt"
	"net/http"
)

// GetUsers from the DB
func GetUsers(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryUsersCRUD(db)

	func(userRepo repository.UserRepository) {
		users, err := userRepo.FindAll()
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}
		responses.JSON(w, http.StatusOK, users)
	}(repo)
}

// CreateUser from the DB
func CreateUser(w http.ResponseWriter, r *http.Request) {
	user := models.User{}
	err := json.NewDecoder(r.Body).Decode(&user)
	if err != nil {
		responses.ERROR(w, http.StatusUnprocessableEntity, err)
		return
	}

	user.Prepare()
	err = user.Validate("")
	if err != nil {
		responses.ERROR(w, http.StatusUnprocessableEntity, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryUsersCRUD(db)

	func(userRepository repository.UserRepository) {
		user, err := userRepository.Save(user)
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}

		w.Header().Set("Location", fmt.Sprintf("%s%s/%d", r.Host, r.RequestURI, user.ID))
		responses.JSON(w, http.StatusCreated, user)
	}(repo)

}

// GetUser from the DB
func GetUser(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryUsersCRUD(db)

	func(userRepository repository.UserRepository) {
		user, err := userRepository.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, user)
	}(repo)

}

// UpdateUser from the DB
func UpdateUser(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	user := models.User{}
	err = json.NewDecoder(r.Body).Decode(&user)
	if err != nil {
		responses.ERROR(w, http.StatusUnprocessableEntity, err)
		return
	}

	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryUsersCRUD(db)

	func(userRepository repository.UserRepository) {
		rows, err := userRepository.Update(uint32(uid), user)
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, rows)
	}(repo)
}

// DeleteUser from the DB
func DeleteUser(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryUsersCRUD(db)

	func(userRepository repository.UserRepository) {
		_, err = userRepository.Delete(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}

		w.Header().Set("Entity", fmt.Sprintf("%d", uid))
		responses.JSON(w, http.StatusNoContent, "")
	}(repo)
}
