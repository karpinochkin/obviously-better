package routes

import (
	"ChampionshipAPI/api/controllers"
	"net/http"
)

var memberRoutes = []Route{
	Route{
		URI:          "/members",
		Method:       http.MethodGet,
		Handler:      controllers.GetMembers,
		AuthRequired: false,
	},
	Route{
		URI:          "/members",
		Method:       http.MethodPost,
		Handler:      controllers.CreateMember,
		AuthRequired: true,
	},
	Route{
		URI:          "/members/{id}",
		Method:       http.MethodGet,
		Handler:      controllers.GetMember,
		AuthRequired: false,
	},
	Route{
		URI:          "/members/{id}",
		Method:       http.MethodPut,
		Handler:      controllers.UpdateMember,
		AuthRequired: true,
	},
	Route{
		URI:          "/members/{id}",
		Method:       http.MethodDelete,
		Handler:      controllers.DeleteMember,
		AuthRequired: true,
	},
	Route{
		URI:          "/members/{id}/image",
		Method:       http.MethodGet,
		Handler:      controllers.GetMemberImage,
		AuthRequired: false,
	},
}
