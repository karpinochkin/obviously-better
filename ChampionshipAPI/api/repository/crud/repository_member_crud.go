package crud

import (
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/utils/channels"
	"errors"

	"github.com/jinzhu/gorm"
)

// RepositoryMemberCRUD is the struct for the member CRUD
type RepositoryMemberCRUD struct {
	db *gorm.DB
}

// NewRepositoryMemberCRUD returns a new repository with DB connection
func NewRepositoryMemberCRUD(db *gorm.DB) *RepositoryMemberCRUD {
	return &RepositoryMemberCRUD{db}
}

// FindAll returns all the members from the DB
// FindAll возвращает всех участников из бд
func (r *RepositoryMemberCRUD) FindAll() ([]models.Member, error) {
	var err error
	members := []models.Member{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("MemberType").Limit(100).Find(&members).Error
		if err != nil {
			ch <- false
			return
		}

		ch <- true
	}(done)
	if channels.OK(done) {
		return members, nil
	}
	return nil, err

}

// FindByID returns an member from the DB
// FindByID возвращает участника по указанному айди из бд
func (r *RepositoryMemberCRUD) FindByID(uid uint32) (models.Member, error) {
	var err error
	member := models.Member{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("MemberType").Find(&member, uid).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return member, nil
	}

	if gorm.IsRecordNotFoundError(err) {
		return models.Member{}, errors.New("Member Not Found")
	}
	return models.Member{}, err

}

// Count returns number of rows in the table
// Count возвращает количество строк в таблице
func (r *RepositoryMemberCRUD) Count() (uint32, error) {
	var count uint32
	var err error
	done := make(chan bool)

	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Model(&models.Member{}).Count(&count).Error
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
