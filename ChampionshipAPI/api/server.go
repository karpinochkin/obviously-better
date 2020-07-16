package api

import (
	"ChampionshipAPI/api/router"
	"ChampionshipAPI/auto"
	"ChampionshipAPI/config"
	"fmt"
	"log"
	"net/http"
)

func init() {
	config.Load()
	auto.Load()
}

// Run : server starting
func Run() {
	fmt.Println("listening...", config.PORT)
	listen(config.PORT)
}

func listen(port int) {
	r := router.New()
	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", port), r))
}
