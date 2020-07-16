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

// GetAllRating from the DB
func GetAllRating(w http.ResponseWriter, r *http.Request) {
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryRatingCRUD(db)

	func(RatingRepo repository.RatingRepository) {
		ratings, err := RatingRepo.FindAll()
		if err != nil {
			responses.ERROR(w, http.StatusUnprocessableEntity, err)
			return
		}
		responses.JSON(w, http.StatusOK, ratings)
	}(repo)
}

// CreateRatingRow from the DB
func CreateRatingRow(w http.ResponseWriter, r *http.Request) {
	fmt.Println("create")
	// Выходной срез
	output := []models.Rating{}
	var currentContestID uint64

	// получение тела ответа
	newRating := []models.Rating{}
	err := json.NewDecoder(r.Body).Decode(&newRating)
	if err != nil {
		responses.ERROR(w, http.StatusUnprocessableEntity, err)
		return
	}

	// Подключение к бд
	db, err := database.Connect()
	if err != nil {
		responses.ERROR(w, http.StatusInternalServerError, err)
		return
	}
	defer db.Close()

	repo := crud.NewRepositoryRatingCRUD(db)

	func(ratingRepo repository.RatingRepository) {

		for _, val := range newRating {

			fmt.Println(newRating)
			// Проверка на правильность полученных данных
			err := val.Validate()
			if err != nil {
				responses.ERROR(w, http.StatusUnprocessableEntity, err)
				return
			}

			// Есть ли такая строка в бд?
			currentRate, err := isConsistsOfDatabase(val, ratingRepo)
			if err != nil {
				// добавляем новую строку статистики
				val, err = ratingRepo.Save(val)
				if err != nil {
					responses.ERROR(w, http.StatusBadRequest, err)
					return
				}
			} else {
				// обновляем существующую строку update
				val.ID = currentRate.ID
				val.Points += currentRate.Points
				_, err := ratingRepo.Update(uint32(val.ID), val)
				if err != nil {
					responses.ERROR(w, http.StatusBadRequest, err)
					return
				}
			}
			output = append(output, val)
			currentContestID = val.ContestID
		}

		responses.JSON(w, http.StatusOK, output)
	}(repo)

	repoContest := crud.NewRepositoryContestCRUD(db)
	func(contestRepo repository.ContestRepository) {
		contest, err := contestRepo.FindByID(uint32(currentContestID))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		contest.CountPlay++
		contestRepo.Update(uint32(contest.ID), contest)

	}(repoContest)

	fmt.Println("finished")

}

func isConsistsOfDatabase(stat models.Rating, ratingRepo repository.RatingRepository) (models.Rating, error) {
	rate, err := ratingRepo.ConsistOf(stat)
	return rate, err
}

// GetRatingRow from DB
func GetRatingRow(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryRatingCRUD(db)

	func(ratingRepo repository.RatingRepository) {
		rating, err := ratingRepo.FindByID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, rating)
	}(repo)

}

// GetRatingByContest from the DB
func GetRatingByContest(w http.ResponseWriter, r *http.Request) {
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

	repo := crud.NewRepositoryRatingCRUD(db)

	func(ratingRepo repository.RatingRepository) {
		rating, err := ratingRepo.FindByContestID(uint32(uid))
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, rating)
	}(repo)
}

// UpdateRatingRow from DB
func UpdateRatingRow(w http.ResponseWriter, r *http.Request) {
	uid, err := VarsUint("id", r)
	if err != nil {
		responses.ERROR(w, http.StatusBadRequest, err)
		return
	}

	rate := models.Rating{}
	err = json.NewDecoder(r.Body).Decode(&rate)
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

	repo := crud.NewRepositoryRatingCRUD(db)

	func(rateRepo repository.RatingRepository) {
		rows, err := rateRepo.Update(uint32(uid), rate)
		if err != nil {
			responses.ERROR(w, http.StatusBadRequest, err)
			return
		}
		responses.JSON(w, http.StatusOK, rows)
	}(repo)
}

// DeleteRatingRow from DB
func DeleteRatingRow(w http.ResponseWriter, r *http.Request) {
	//////////////////////////////////////////////////////////
}
