
void setup() {
  size(600, 400);
  
  ellipse(260, 60, 60, 60);
  line(260, 90, 260, 200);
  
  // Arm on the left
  fill(0, 0, 0);
  line(260, 90, 200, 120);
  line(200, 120, 220, 160);
  ellipse(220, 160, 20, 20);
  
  // Arm on the right
  line(260, 90, 320, 120);
  line(320, 120, 360, 90);
  ellipse(360, 90, 20, 20);
  
  // Leg on the left
  line(260, 200, 210, 220);
  line(210, 220, 220, 270);
  line(220, 270, 200, 270);
  
  // Leg on the right
  line(260, 200, 300, 220);
  line(300, 220, 330, 270);
  line(330, 270, 350, 260);
}

void draw() {
  
}