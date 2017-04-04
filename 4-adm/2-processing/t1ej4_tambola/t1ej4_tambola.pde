
float avg = 0;
float MAX_VEL = 30;
float OLD_WEIGHT = 0.8;

void setup() {
  size(640, 480);
  colorMode(HSB, 100);
  noStroke();
}

void draw() {
  background(0, 0, 0);
  
  float vel = sqrt(pow(pmouseX - mouseX, 2) + pow(pmouseY - mouseY, 2));
  if (vel > MAX_VEL) {
    vel = MAX_VEL;
  }

  // Apply IIR filter
  avg = avg * OLD_WEIGHT + vel * (1 - OLD_WEIGHT) / MAX_VEL;

  float size = sin(4.5 * PI * avg) * MAX_WIDTH;
  
  fill(255, 255, 255);
  ellipse(mouseX, mouseY, size, size);
}