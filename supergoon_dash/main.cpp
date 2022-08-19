#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_dash/actors/trampoline.hpp>
#include <supergoon_dash/actors/player.hpp>
#include <supergoon_dash/actors/level_end.hpp>

int main([[maybe_unused]]int argv, [[maybe_unused]]char **args)
{
	// Add to our actor factory so that they can be spawned from the tilemap
	Objects::Actor::actor_listing_vector.push_back(std::make_pair("player", Player::ActorFactory));
	Objects::Actor::actor_listing_vector.push_back(std::make_pair("trampoline", Trampoline::ActorFactory));
	Objects::Actor::actor_listing_vector.push_back(std::make_pair("level_end", LevelEnd::ActorFactory));
	auto world = World();
	world.Run();
	return 1;
}
