package database

import (
	"ChampionshipAPI/config"

	_ "github.com/go-sql-driver/mysql"
	"github.com/jinzhu/gorm"
)

// Connect to the DATABASE
// Соединение с БД
func Connect() (*gorm.DB, error) {
	db, err := gorm.Open(config.DBDRIVER, config.DBNAME)
	if err != nil {
		return nil, err
	}
	return db, nil
}
