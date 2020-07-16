package models

import "errors"

// TypeMember model
type TypeMember struct {
	ID     uint64   `gorm:"primary_id;auto_increment;not null" json:"id"`
	Name   string   `gorm:"size:45;not null;" json:"name"`
	Member []Member `gorm:"many2many:member_has_mebmer_type;"`
}

// Validate validates the inputs
func (t *TypeMember) Validate(action string) error {
	if t.Name == "" {
		return errors.New("type name is required")
	}
	return nil
}
