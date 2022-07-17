#include <supergoon_engine/engine/world.hpp>
#include <supergoon_engine/objects/actor.hpp>
#include <supergoon_dash/actors/player.hpp>

int main([[maybe_unused]]int argv, [[maybe_unused]]char **args)
{
	// Add to our actor factory so that they can be spawned from the tilemap
	Objects::Actor::actor_listing_vector.push_back(std::make_pair("player", Player::ActorFactory));
	auto world = World();
	world.Run();
	return 1;
}
