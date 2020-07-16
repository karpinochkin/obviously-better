package models

import "errors"

// Rating Model
type Rating struct {
	ID        uint64  `gorm:"primary_id;auto_increment;not null;" json:"id"`
	Points    float64 `gorm:"not null;"`
	Contest   Contest `gorm:"foreignkey:ContestID;" json:"contest"`
	ContestID uint64  `gorm:"not null;" json:"contest_id"`
	Member    Member  `gorm:"foreignkey:MemberID;" json:"member"`
	MemberID  uint64  `gorm:"not null;" json:"member_id"`
}

// TableName : change table name
func (Rating) TableName() string {
	return "rating"
}

// Validate validates the inputs
func (r *Rating) Validate() error {
	if r.Points <= 0.0 {
		return errors.New("points value is invalid")
	}
	if r.ContestID <= 0 {
		return errors.New("contest id is invalid")
	}
	if r.MemberID <= 0 {
		return errors.New("member id is invalid")
	}
	return nil
}
