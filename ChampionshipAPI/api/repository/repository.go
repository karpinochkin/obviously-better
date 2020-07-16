package repository

import (
	"ChampionshipAPI/api/models"
)

// UserRepository is the interface User CRUD
type UserRepository interface {
	Save(models.User) (models.User, error)
	FindAll() ([]models.User, error)
	FindByID(uint32) (models.User, error)
	Update(uint32, models.User) (int64, error)
	Delete(uint32) (int64, error)
}

// MemberTypeRepository is the interface Member Type CRUD
type MemberTypeRepository interface {
	Save(models.TypeMember) (models.TypeMember, error)
	FindAll() ([]models.TypeMember, error)
	FindByID(uint32) (models.TypeMember, error)
	Update(uint32, models.TypeMember) (int64, error)
	Delete(uint32) (int64, error)
	Count() (uint32, error)
	CountMembers(uint32) (uint32, error)
}

// MemberRepository is the interface Member CRUD
type MemberRepository interface {
	// Save(models.TypeMember) (models.TypeMember, error)
	FindAll() ([]models.Member, error)
	FindByID(uint32) (models.Member, error)
	Count() (uint32, error)
	// Update(uint32, models.TypeMember) (int64, error)
	// Delete(uint32) (int64, error)
}

// ContestRepository is the interface Contest CRUD
type ContestRepository interface {
	FindAll() ([]models.Contest, error)
	FindByID(uint32) (models.Contest, error)
	Count() (uint32, error)
	CountMemberTypes(uint32) (uint32, error)
	FindAllByRange(uint32, uint32) ([]models.Contest, error)
	Update(uint32, models.Contest) (int64, error)
}

// RatingRepository is the interface Contest CRUD
type RatingRepository interface {
	Save(models.Rating) (models.Rating, error)
	Update(uint32, models.Rating) (int64, error)
	FindAll() ([]models.Rating, error)
	FindByID(uint32) (models.Rating, error)
	FindByContestID(uint32) ([]models.Rating, error)
	ConsistOf(models.Rating) (models.Rating, error)
}
