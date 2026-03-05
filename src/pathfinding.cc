#include "ButtonArduino.h"
#include "WMath.h"
#include <DFMicrobit_Radio.h>
#include <Microbit_Matrix.h>
#include <Microbit_Sensors.h>
#include <stdbool.h>

#define MAP_ROW 5
#define MAP_COLUMN 5
#define GRID_COUNT (MAP_ROW * MAP_COLUMN)

void pathfinding_bfs(int start, int stop);

// 格子
typedef struct _Grid {
  // 索引
  int i;
  // 夫索引
  int pi;
} Grid;

Grid grids[GRID_COUNT] = {0};

int coord2index(int x, int y) { return y * MAP_COLUMN + x; }

void index2coord(int index, int *x, int *y) {
  *x = index % MAP_COLUMN;
  *y = index / MAP_COLUMN;
}

// 主程序开始
void setup() {
  dfrobotRandomSeed();
  for (int i = 0; i < GRID_COUNT; ++i) {
    grids[i].i = i;
    grids[i].pi = -1;
  }
}

typedef enum _Status {
  Idle,
  Busy,
} Status;

Status status = Status::Idle;

int start_point = -1;
int stop_point = -1;

void loop() {
  if (Status::Idle == status && Button_A.isPressed()) { // 设置起点
    MMatrix.clear();
    start_point = random(25);
  } else if (Status::Idle == status && Button_B.isPressed()) { // 设置终点
    MMatrix.clear();
    stop_point = random(25);
  } else if (Status::Idle == status && Button_AB.isPressed()) { // 开始寻路
    if (-1 != start_point && -1 != stop_point) {
      status = Status::Busy;
      pathfinding_bfs(start_point, stop_point);
      start_point = -1;
      stop_point = -1;
      MMatrix.clear();
    }
  }

  if (Status::Idle == status) {
    int x;
    int y;
    if (-1 != start_point) {
      index2coord(start_point, &x, &y);
      MMatrix.drawPixel(x, y, LED_ON);
    }
    if (-1 != stop_point) {
      index2coord(stop_point, &x, &y);
      MMatrix.drawPixel(x, y, LED_ON);
    }
  } else if (Status::Busy == status) {
  }
}

void pathfinding_bfs(int start_point, int stop_point) {

}
