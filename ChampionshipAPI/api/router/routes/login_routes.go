package routes

import (
	"ChampionshipAPI/api/controllers"
	"net/http"
)

var loginRoutes = []Route{
	Route{
		URI:          "/login",
		Method:       http.MethodPost,
		Handler:      controllers.Login,
		AuthRequired: false,
	},
}
