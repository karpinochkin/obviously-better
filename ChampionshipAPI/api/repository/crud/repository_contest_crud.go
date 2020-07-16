package crud

import (
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/utils/channels"
	"errors"

	"github.com/jinzhu/gorm"
)

// RepositoryContestCRUD is the struct for the contest CRUD
type RepositoryContestCRUD struct {
	db *gorm.DB
}

// NewRepositoryContestCRUD returns a new repository with DB connection
func NewRepositoryContestCRUD(db *gorm.DB) *RepositoryContestCRUD {
	return &RepositoryContestCRUD{db}
}

// FindAll returns all the contests from the DB
// FindAll возвращает слайс всех соревнований из бд
func (r *RepositoryContestCRUD) FindAll() ([]models.Contest, error) {
	var err error
	contests := []models.Contest{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("MemberType").Limit(100).Find(&contests).Error
		if err != nil {
			ch <- false
			return
		}

		ch <- true
	}(done)
	if channels.OK(done) {
		return contests, nil
	}
	return nil, err
}

// FindByID returns an contest by id from the DB
// FindByID возвращает соревнование (по указанному айди) из бд
func (r *RepositoryContestCRUD) FindByID(uid uint32) (models.Contest, error) {
	var err error
	contest := models.Contest{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("MemberType").Find(&contest, uid).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return contest, nil
	}

	if gorm.IsRecordNotFoundError(err) {
		return models.Contest{}, errors.New("Member Not Found")
	}
	return models.Contest{}, err

}

// Count returns number of rows in the table
// Count возвращает количество строк в таблице
func (r *RepositoryContestCRUD) Count() (uint32, error) {
	var count uint32
	var err error
	done := make(chan bool)

	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Model(&models.Contest{}).Count(&count).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return count, nil
	}
	return 0, err
}

// CountMemberTypes returns number of member types in the contest (id)
// CountMemberTypes возвращает количество типов участников для указанного соревнования
func (r *RepositoryContestCRUD) CountMemberTypes(id uint32) (uint32, error) {
	contest, err := r.FindByID(id)
	if err != nil {
		return 0, err
	}
	return uint32(len(contest.MemberType)), nil
}

// FindAllByRange returns contest slice by the specified range
// FindAllByRange возвращает слайс соревнований из указанного диапазона айди
func (r *RepositoryContestCRUD) FindAllByRange(startID uint32, endID uint32) ([]models.Contest, error) {
	var err error
	contests := []models.Contest{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("MemberType").
			Where("id >= ? AND id <= ?", startID, endID).
			Limit(100).Find(&contests).Error
		if err != nil {
			ch <- false
			return
		}

		ch <- true
	}(done)
	if channels.OK(done) {
		return contests, nil
	}
	return nil, err
}

func (r *RepositoryContestCRUD) Update(uid uint32, contest models.Contest) (int64, error) {
	var rs *gorm.DB
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		rs = r.db.Debug().Model(&models.Contest{}).Where("id = ?", uid).Take(&models.Contest{}).UpdateColumns(
			map[string]interface{}{
				"name":        contest.Name,
				"description": contest.Description,
				"count_play":  contest.CountPlay,
				"image":       contest.Image,
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
