void setup() {
  size(480, 640);
  dels = new boolean[13 * 6];
}

boolean dels[];

int rowcol[] = {
  128, 128, 128,
  255,   0,   0,
  255, 255,   0,
    0,   0, 255,
  255,   0, 255,
    0, 255,   0
};

void draw() {

  background(0, 0, 0);
  
  fill(128, 128, 128);
  noStroke();
  rect(0, 40, 480, 20);
  rect(0, 40, 20, 600);
  rect(460, 40, 20, 600);
  
  for (int y = 0; y < 6; y++) {
    fill(rowcol[y * 3 + 0], rowcol[y * 3 + 1], rowcol[y * 3 + 2]);
    
    for (int x = 0; x < 13; x++) {
      
      if (!dels[y * 13 + x]) {
        rect(24 + 33.23 * x, 120 + y * 18, 30, 16);
      }
    }
  }
  
}

void mouseClicked() {
  int col = int(floor(mouseX - 24) / 33.23);
  int row = int(floor(mouseY - 120) / 18);
  if (col < 0 || col > 13 || row < 0 || row > 5) {
    return;
  }
  
  dels[row * 13 + col] = true;
}