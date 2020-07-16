package models

import "errors"

// Contest model
type Contest struct {
	ID          uint64       `gorm:"primary_id;auto_increment;not null" json:"id"`
	Name        string       `gorm:"size:45;not null;" json:"name"`
	Description string       `gorm:"size:256;not null;" json:"description"`
	CountPlay   uint64       `gorm:"default:0" json:"count_play"`
	Image       []byte       `json:"image"`
	MemberType  []TypeMember `gorm:"many2many:contest_has_member_type;"`
}

// Validate validates the inputs
func (c *Contest) Validate() error {
	if c.Name == "" {
		return errors.New("name is required")
	}
	if c.Description == "" {
		return errors.New("description is required")
	}
	return nil
}
