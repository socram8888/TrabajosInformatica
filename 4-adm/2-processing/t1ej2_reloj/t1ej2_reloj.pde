
void setup() {
  size(200, 200);
}

void draw() {
  background(255, 255, 255);
  
  fill(255, 255, 255);
  ellipse(100, 100, 200, 200);
  fill(0, 0, 0);
  
  pushMatrix();
  translate(100, 100);
  rotate(radians(6 * second()));
  line(0, 0, 0, -80);
  popMatrix();
  
  pushMatrix();
  translate(100, 100);
  rotate(radians(6 * minute()));
  rect(-1, -60, 2, 60);
  popMatrix();
  
  pushMatrix();
  translate(100, 100);
  rotate(radians(360 * hour() / 24));
  rect(-2, -40, 4, 40);
  popMatrix();
}