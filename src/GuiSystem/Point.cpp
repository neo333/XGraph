#include <XGraph/GuiSystem/Point.h>

std::ostream& operator<<(std::ostream& con,const Point& point){
	con << point.x << " - " << point.y;
	return con;
}