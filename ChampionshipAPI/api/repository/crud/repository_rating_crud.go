package crud

import (
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/utils/channels"
	"errors"

	"github.com/jinzhu/gorm"
)

// RepositoryRatingCRUD is the struct for the Rating CRUD
type RepositoryRatingCRUD struct {
	db *gorm.DB
}

// NewRepositoryRatingCRUD returns a new repository with DB connection
func NewRepositoryRatingCRUD(db *gorm.DB) *RepositoryRatingCRUD {
	return &RepositoryRatingCRUD{db}
}

// FindAll returns all the Ratings from the DB
// FindAll возвращает все значения существующих записей в таблице Рейтинга
func (r *RepositoryRatingCRUD) FindAll() ([]models.Rating, error) {
	var err error
	rating := []models.Rating{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("Member").Preload("Contest").Limit(100).Find(&rating).Error
		if err != nil {
			ch <- false
			return
		}

		ch <- true
	}(done)
	if channels.OK(done) {
		return rating, nil
	}
	return nil, err

}

// FindByID returns an rating from the DB
// FindByID возвращает строку рейтинга с соответствующим индентификатором
func (r *RepositoryRatingCRUD) FindByID(uid uint32) (models.Rating, error) {
	var err error
	rating := models.Rating{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("Member").Preload("Contest").Find(&rating, uid).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return rating, nil
	}

	if gorm.IsRecordNotFoundError(err) {
		return models.Rating{}, errors.New("rating Not Found")
	}
	return models.Rating{}, err

}

// FindByContestID returns contests slice from DB
// FindByContestID возвращает слайс соревнований из таблицы Рейтинга с указанным значением
// идентификатора соревнования (contest_id) в количестве 20 записей в отсортированном виде по количеству очков
func (r *RepositoryRatingCRUD) FindByContestID(contestID uint32) ([]models.Rating, error) {
	var err error
	rating := []models.Rating{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Limit(20).Order("points DESC").Preload("Member").Preload("Contest").Where("contest_id = ?", contestID).Find(&rating).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return rating, nil
	}
	return nil, err
}

func (r *RepositoryRatingCRUD) Save(rating models.Rating) (models.Rating, error) {
	var err error
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Model(&models.Rating{}).Create(&rating).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return rating, nil
	}
	return models.Rating{}, err
}

func (r *RepositoryRatingCRUD) Update(id uint32, rate models.Rating) (int64, error) {
	var rs *gorm.DB
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		rs = r.db.Debug().Model(&models.Rating{}).Where("id = ?", id).Take(&models.Rating{}).UpdateColumns(
			map[string]interface{}{
				"points":     rate.Points,
				"contest_id": rate.ContestID,
				"member_id":  rate.MemberID,
			},
		)
		ch <- true
	}(done)

	if channels.OK(done) {
		if rs.Error != nil {
			return 0, rs.Error
		}

		return rs.RowsAffected, nil
	}
	return 0, rs.Error
}

// ConsistOf возвращает строку рейтинга, если точка продаж находится в таблице
// возвращает пустой элемент и ошибку, если не находится
func (r *RepositoryRatingCRUD) ConsistOf(stat models.Rating) (models.Rating, error) {
	var err error
	var rating = models.Rating{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Where("contest_id = ?", stat.ContestID).Where("member_id = ?", stat.MemberID).Take(&rating).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return rating, nil
	}
	return models.Rating{}, err
}
