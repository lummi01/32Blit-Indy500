#include "indy.hpp"
#include "assets.hpp"

using namespace blit;

int player;
std::string status;

Surface *backdrop,*carsprites;

typedef std::vector<Vec2> shape;
shape innerarea, outerarea, waypoints;

typedef struct car {
	int sprite;
	Vec2 pos;
	Vec2 dir;
	float angle = 3.14f;
	float speed;
	int waypt;
	int distance;
	int rank;
} car;

car cars[2];

Rect cone = Rect ( 0,16,16,40);
Vec2 FinishLine = Vec2(79,89);

void set_tracklimits() {
// polygon inside track - sandy area
// 
	innerarea = { Vec2(38,75), Vec2(37,74), Vec2(37,74), Vec2(36,73), Vec2(36,55),
              Vec2(36,38), Vec2(37,37), Vec2(37,37), Vec2(38,36),
              Vec2(41,36), Vec2(42,37), Vec2(42,37), Vec2(43,38),
              Vec2(50,53), Vec2(58,61), Vec2(74,68),
              Vec2(85,68), Vec2(101,61), Vec2(109,53),
              Vec2(116,38), Vec2(117,37), Vec2(117,37), Vec2(118,36),
              Vec2(121,36), Vec2(122,37), Vec2(122,37), Vec2(123,38),
              Vec2(123,73), Vec2(122,74), Vec2(122,74), Vec2(121,75),
              Vec2(38,75)};

// polygon surrounding track - sandy area
	outerarea = { Vec2(34,108), Vec2(18,101), Vec2(10,93), Vec2(3,77), Vec2(3,55),
              Vec2(3,34), Vec2(10,18), Vec2(18,10), Vec2(34,3),
              Vec2(45,3), Vec2(61,10), Vec2(69,18), Vec2(76,33),
              Vec2(77,34), Vec2(77,34), Vec2(78,35),
              Vec2(81,35), Vec2(82,34), Vec2(82,34),
              Vec2(83,33), Vec2(90,18), Vec2(98,10), Vec2(114,3),
              Vec2(125,3), Vec2(141,10), Vec2(149,18), Vec2(156,34),
              Vec2(156,77), Vec2(149,93), Vec2(141,101), Vec2(125,108),
              Vec2(34,108)};

//	float scale = screen.bounds.w / 160.0f;
//		for ( auto &p : innerarea) p.x = (float)p.x * scale;
//		for ( auto &p : outerarea) p.x = (float)p.x * scale;
}
void set_waypoints(){
int i=0;
	for (auto &inner: innerarea) {
		Vec2 outer = outerarea[i++];
		Vec2 dest;
		// get points half way between inner and outer track 
		// i.e. middle of track to guide AI
		dest.x = inner.x + ( (outer.x - inner.x ) / 2);
		dest.y = inner.y + ( (outer.y - inner.y ) / 2);
		waypoints.push_back(dest);
	}
}

float ang_to_point ( Vec2 point, Vec2 dest ) {
// return angle of vector between points

	Vec2 diff = dest - point;
	float angle = atan2( diff.y , diff.x );
	return (angle);
}

bool point_inside_shape ( Vec2 point, shape shape ){
// check a given point is enclosed by a polygon
// http://erich.realtimerendering.com/ptinpoly/ for an explanation !

  int i, j, nvert = shape.size();
  bool c = false;

  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
    if( ( (shape[i].y >= point.y ) != (shape[j].y >= point.y) ) &&
        (point.x <= (shape[j].x - shape[i].x) * (point.y - shape[i].y) / (shape[j].y - shape[i].y) + shape[i].x)
      )
      c = !c;
  }

  return c;
}

bool near(Vec2 point,Vec2 target, int howfar){
	return ( (abs(point.x - target.x) < howfar ) && (abs(point.y - target.y) < howfar));
}

void blit_rotate_sprite (Surface *sprite,int src, float angle, Vec2 screenpos) {
//rotate a sprite to screen at any angle
Vec2 rot;
    float sinangle = sin(angle);
    float cosangle = cos(angle);
    for (int x=0;x<9;x++)
	    for (int y=0;y<9;y++) {
		    int x1 = x - 5;
		    int y1 = y - 5;
		    rot.x = x1 * sinangle + (y1 * cosangle);
		    rot.y = y1 * sinangle - (x1 * cosangle);
		    Vec2 pos = rot + screenpos;
        	    screen.stretch_blit(sprite,Rect(src*10 + x, y,1,1),Rect(pos.x, pos.y,1,1));
	    }
}

void init() {
    set_screen_mode(ScreenMode::lores);

    backdrop = Surface::load(trackimg);
    carsprites = Surface::load(carimg);

    carsprites->palette[0] = Pen(0,0,0,0); //transparent

    set_tracklimits();
    set_waypoints();

    // car starting positions on grid
    int spritenum = 0;
    //int speed = 0;
    for (auto &car: cars) {
    	car.pos = Vec2(FinishLine.x,FinishLine.y + (spritenum * 10));
    	car.sprite = spritenum;
	car.speed = 0.5f + (rand()%5 *.1f);
	spritenum++;
    }
}

void render(uint32_t time) {
// static uint32_t start = time;
//static int lastlap,bestlap,clock;

    // Draw track
    screen.stretch_blit(backdrop,Rect(0,0,160,120),Rect(0,0,screen.bounds.w,screen.bounds.h));

    // Draw cars
    for (auto &car: cars){
    	blit_rotate_sprite(carsprites, car.sprite, car.angle, car.pos);
	}


    // Draw score
    screen.pen = Pen(255,255,255);
//    clock = (time - start) / 100;
//    status = "1st 2nd 3rd 4th";
//    screen.text(status, minimal_font, Vec2(13,0));
//    status = "Position: " + std::to_string(cars[0].rank);
//    screen.text(status, minimal_font, Vec2(screen.bounds.w-60,0));
//    status = "Lap : 1 / 3";
//    screen.text(status, minimal_font, Vec2(screen.bounds.w-60,10));
//    status = "Lap time: " + std::to_string(clock);
//    screen.text(status, minimal_font, Vec2(0, screen.bounds.h - 10));
//    status = "Last: " + std::to_string(lastlap);
//    screen.text(status, minimal_font, Vec2(screen.bounds.w / 2, screen.bounds.h - 10));
//    status = "Best: " + std::to_string(bestlap);
//    screen.text(status, minimal_font, Vec2(screen.bounds.w - 50, screen.bounds.h - 10));
//    screen.text(std::to_string(cars[0].angle), minimal_font, Vec2(3,110));
    // Manage laps
    if (near (cars[player].pos,FinishLine,20)) {
//	    if (clock > 50) lastlap = clock;
//	    if (lastlap < bestlap || bestlap == 0) bestlap = lastlap;
//	    start = time;
    	    }
}
	
void update(uint32_t time) {

    if (pressed(Button::DPAD_LEFT)  || joystick.x < -0.2f) cars[player].angle -= 0.03f;
    if (pressed(Button::DPAD_RIGHT) || joystick.x > 0.2f)  cars[player].angle += 0.03f;

    if (pressed(Button::A) && cars[player].speed < 1.6f ) cars[player].speed += 0.02f;

    // slow car if off track 
    if (point_inside_shape(cars[player].pos,innerarea) || !point_inside_shape(cars[player].pos,outerarea)) 
		    cars[player].speed = 0.2;

    // Move all cars (including player's car)
    bool aicar = false;
    for (auto &car: cars){
	    float angle = car.angle;
            car.dir = Vec2( cos(angle), sin(angle));
            car.pos += car.dir * car.speed;

	    int dist = 50;
	    if (aicar){
		    // AI follows waypoints
		    // point car at checkpoint
		    float angle = ang_to_point( car.pos, waypoints[car.waypt]);
	            car.angle = angle;
		    dist = 10;
		    }

	    if (near(car.pos,waypoints[car.waypt],dist)) {
			    //move target to next checkpoint if near current one
			    car.waypt++;
			    if (car.waypt == (int) waypoints.size()) car.waypt = 1;
			    car.distance++;
	    	    	    }
    	   //Get car ranking by distance travelled
	   int rank=1;
    	   for (auto &othercar: cars){
	    	if (car.distance < othercar.distance) rank++;
	   }
	   car.rank = rank;
	   aicar = true;
    }
    // player car gradually slows down 
    cars[player].speed *= 0.98f;
}
