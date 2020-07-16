package models

import "errors"

// Member model
type Member struct {
	ID          uint64       `gorm:"primary_id;auto_increment;not null" json:"id"`
	Name        string       `gorm:"size:45;not null;" json:"name"`
	Description string       `gorm:"size:256;" json:"description"`
	Image       []byte       `json:"image"`
	MemberType  []TypeMember `gorm:"many2many:member_has_mebmer_type;"`
}

// MemberWithoutImage model
type MemberWithoutImage struct {
	ID          uint64 `gorm:"primary_id;auto_increment;not null" json:"id"`
	Name        string `gorm:"size:45;not null;" json:"name"`
	Description string `gorm:"size:256;" json:"description"`
}

// Validate validates the inputs
func (m *Member) Validate(action string) error {
	if m.Name == "" {
		return errors.New("type name is required")
	}
	return nil
}
