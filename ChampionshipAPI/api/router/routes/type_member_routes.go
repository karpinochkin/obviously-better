package routes

import (
	"ChampionshipAPI/api/controllers"
	"net/http"
)

var typeMemberRoutes = []Route{
	Route{
		URI:          "/membertypes",
		Method:       http.MethodGet,
		Handler:      controllers.GetMemberTypes,
		AuthRequired: false,
	},
	Route{
		URI:          "/membertypes",
		Method:       http.MethodPost,
		Handler:      controllers.CreateMemberType,
		AuthRequired: true,
	},
	Route{
		URI:          "/membertypes/{id}",
		Method:       http.MethodGet,
		Handler:      controllers.GetMemberType,
		AuthRequired: false,
	},
	Route{
		URI:          "/membertypes/{id}",
		Method:       http.MethodPut,
		Handler:      controllers.UpdateMemberType,
		AuthRequired: true,
	},
	Route{
		URI:          "/membertypes/{id}",
		Method:       http.MethodDelete,
		Handler:      controllers.DeleteMemberType,
		AuthRequired: true,
	},
	Route{
		URI:          "/count/membertypes",
		Method:       http.MethodGet,
		Handler:      controllers.CountMemberTypes,
		AuthRequired: false,
	},
	Route{
		URI:          "/membertypes/{id}/count/members",
		Method:       http.MethodGet,
		Handler:      controllers.CountMembersInMemberType,
		AuthRequired: false,
	},
	Route{
		URI:          "/membertypes/random/members",
		Method:       http.MethodPost,
		Handler:      controllers.GetRandomMembersForMemberTypes,
		AuthRequired: false,
	},
}
