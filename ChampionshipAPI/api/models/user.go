package models

import (
	"ChampionshipAPI/api/security"
	"errors"
	"html"
	"strings"

	"github.com/badoux/checkmail"
)

// User model
type User struct {
	ID       uint64 `gorm:"primary_id;auto_increment;not null" json:"id"`
	Email    string `gorm:"size:256;not null;unique" json:"email"`
	Name     string `gorm:"size:45;not null;" json:"name"`
	Surname  string `gorm:"size:45;not null;" json:"surname"`
	Login    string `gorm:"size:45;not null;unique" json:"login"`
	Password string `gorm:"size:60;not null" json:"password,omitempty"`
}

// BeforeSave hash the user password
func (u *User) BeforeSave() error {
	hashedPassword, err := security.Hash(u.Password)
	if err != nil {
		return err
	}
	u.Password = string(hashedPassword)
	return nil
}

// Prepare cleans the inputs
func (u *User) Prepare() {
	u.ID = 0
	u.Login = html.EscapeString(strings.TrimSpace(u.Login))
	u.Email = html.EscapeString(strings.TrimSpace(u.Email))
}

// Validate validates the inputs
func (u *User) Validate(action string) error {
	switch strings.ToLower(action) {
	case "update":
		if u.Login == "" {
			return errors.New("Nickname is required")
		}

		if u.Email == "" {
			return errors.New("Email is required")
		}

		if u.Name == "" {
			return errors.New("Name is required")
		}

		if u.Surname == "" {
			return errors.New("Surname is required")
		}

		if err := checkmail.ValidateFormat(u.Email); err != nil {
			return errors.New("Invalid email")
		}
	case "login":
		if u.Email == "" {
			return errors.New("Email is required")
		}

		if err := checkmail.ValidateFormat(u.Email); err != nil {
			return errors.New("Invalid email")
		}

		if u.Password == "" {
			return errors.New("Password is required")
		}
	default:
		if u.Login == "" {
			return errors.New("Nickname is required")
		}

		if u.Password == "" {
			return errors.New("Password is required")
		}

		if u.Email == "" {
			return errors.New("Email is required")
		}

		if err := checkmail.ValidateFormat(u.Email); err != nil {
			return errors.New("Invalid email")
		}
	}

	return nil
}
