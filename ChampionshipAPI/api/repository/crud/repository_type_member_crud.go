package crud

import (
	"ChampionshipAPI/api/models"
	"ChampionshipAPI/api/utils/channels"
	"errors"

	"github.com/jinzhu/gorm"
)

// RepositoryTypeMemberCRUD is the struct for the User CRUD
type RepositoryTypeMemberCRUD struct {
	db *gorm.DB
}

// NewRepositoryTypeMemberCRUD returns a new repository with DB connection
func NewRepositoryTypeMemberCRUD(db *gorm.DB) *RepositoryTypeMemberCRUD {
	return &RepositoryTypeMemberCRUD{db}
}

// FindAll returns all the member types from the DB
// FindAll возвращает все типы существующих типов участников из базы данных
func (r *RepositoryTypeMemberCRUD) FindAll() ([]models.TypeMember, error) {
	var err error
	memberTypes := []models.TypeMember{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("Member").Limit(100).Find(&memberTypes).Error
		if err != nil {
			ch <- false
			return
		}

		ch <- true
	}(done)
	if channels.OK(done) {
		return memberTypes, nil
	}
	return nil, err
}

// FindByID returns an type member from the DB
// FindByID возвращает тип участников с соответствующим идентификаторов
func (r *RepositoryTypeMemberCRUD) FindByID(uid uint32) (models.TypeMember, error) {
	var err error
	typeMember := models.TypeMember{}
	done := make(chan bool)
	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Preload("Member").Find(&typeMember, uid).Error
		if err != nil {
			ch <- false
			return
		}
		ch <- true
	}(done)
	if channels.OK(done) {
		return typeMember, nil
	}

	if gorm.IsRecordNotFoundError(err) {
		return models.TypeMember{}, errors.New("Type Member Not Found")
	}
	return models.TypeMember{}, err
}

// Count returns number of rows in the table
// Count возвращает количество строк в таблице
func (r *RepositoryTypeMemberCRUD) Count() (uint32, error) {
	var count uint32
	var err error
	done := make(chan bool)

	go func(ch chan<- bool) {
		defer close(ch)
		err = r.db.Debug().Model(&models.TypeMember{}).Count(&count).Error
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

// CountMembers returns number of members in the member type (id)
// CountMembers возвращает количество участников в указанном типе участников
func (r *RepositoryTypeMemberCRUD) CountMembers(id uint32) (uint32, error) {
	memberType, err := r.FindByID(id)
	if err != nil {
		return 0, err
	}
	return uint32(len(memberType.Member)), nil
}

// Update updates an type member from the DB
func (r *RepositoryTypeMemberCRUD) Update(uid uint32, typeMember models.TypeMember) (int64, error) {
	//////////////////////////////////////////////////////////
	return 0, nil
}

// Delete removes an type member from the DB
func (r *RepositoryTypeMemberCRUD) Delete(uid uint32) (int64, error) {
	//////////////////////////////////////////////////////////
	return 0, nil
}

// Save returns a new type member created or an error
func (r *RepositoryTypeMemberCRUD) Save(typeMember models.TypeMember) (models.TypeMember, error) {
	//////////////////////////////////////////////////////////
	return models.TypeMember{}, nil
}
