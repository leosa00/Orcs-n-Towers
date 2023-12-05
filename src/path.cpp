#include "path.hpp"

path::path() {}

void path::addWaypoint(const sf::Vector2f& point) {
    waypoints_.push(point);
	wayPoints.push_back(point);
}

std::queue<sf::Vector2f> path::getWaypoints() const {
    return waypoints_;
}

const float path::width = 60.f;
void path::makeUnBuildablePath()
{
	sf::FloatRect partofStreet;

	for (size_t i = 0; i < wayPoints.size() - 1; ++i)
	{
		sf::Vector2f vector;

		vector.x = wayPoints[i + 1].x - wayPoints[i].x;
		vector.y = wayPoints[i + 1].y - wayPoints[i].y;

		if ((vector.x >= 0.f) && (vector.y >= 0.f))
		{
			partofStreet.left = wayPoints[i].x - width / 2;
			partofStreet.top = wayPoints[i].y - width / 2;
			partofStreet.width = vector.x + width;
			partofStreet.height = vector.y + width;
		}
		else if ((vector.x < 0.f) || (vector.y < 0))
		{
			partofStreet.left = wayPoints[i + 1].x - width / 2;
			partofStreet.top = wayPoints[i + 1].y - width / 2;
			partofStreet.width = fabs(vector.x) + width;
			partofStreet.height = fabs(vector.y) + width;
		}

		unBuildable.push_back(partofStreet);
	}
	//wayPoints.clear();
}