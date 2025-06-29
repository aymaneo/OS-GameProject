#include "sprite.h"

unsigned char palette_vga[256][3] = {
  {0, 0, 0},
  {4, 4, 4},
  {8, 8, 8},
  {12, 12, 12},
  {16, 16, 16},
  {21, 21, 21},
  {25, 25, 25},
  {29, 29, 29},
  {33, 33, 33},
  {37, 37, 37},
  {42, 42, 42},
  {46, 46, 46},
  {50, 50, 50},
  {54, 54, 54},
  {58, 58, 58},
  {63, 63, 63},
  {6, 1, 0},
  {10, 5, 0},
  {14, 10, 0},
  {18, 14, 0},
  {22, 18, 0},
  {27, 22, 0},
  {31, 26, 0},
  {35, 31, 2},
  {39, 35, 6},
  {44, 39, 10},
  {48, 43, 14},
  {52, 47, 19},
  {56, 52, 23},
  {61, 56, 27},
  {63, 60, 32},
  {63, 63, 37},
  {12, 0, 0},
  {15, 0, 0},
  {20, 5, 0},
  {24, 9, 0},
  {28, 14, 0},
  {33, 18, 0},
  {37, 22, 2},
  {41, 26, 6},
  {45, 30, 10},
  {49, 35, 15},
  {54, 39, 19},
  {58, 43, 23},
  {62, 47, 27},
  {63, 51, 32},
  {63, 56, 38},
  {63, 60, 43},
  {16, 0, 0},
  {19, 0, 0},
  {23, 1, 0},
  {27, 6, 0},
  {32, 10, 3},
  {36, 14, 7},
  {40, 18, 11},
  {44, 22, 15},
  {48, 27, 20},
  {53, 31, 24},
  {57, 35, 28},
  {61, 39, 32},
  {63, 43, 37},
  {63, 48, 42},
  {63, 52, 48},
  {63, 56, 53},
  {16, 0, 0},
  {19, 0, 3},
  {23, 0, 6},
  {28, 3, 10},
  {32, 7, 14},
  {36, 12, 19},
  {40, 16, 23},
  {44, 20, 27},
  {49, 24, 31},
  {53, 28, 35},
  {57, 33, 40},
  {61, 37, 44},
  {63, 41, 49},
  {63, 45, 54},
  {63, 49, 59},
  {62, 54, 60},
  {12, 0, 13},
  {16, 0, 16},
  {21, 0, 18},
  {25, 2, 22},
  {29, 7, 26},
  {33, 11, 31},
  {37, 15, 35},
  {42, 19, 39},
  {46, 23, 43},
  {50, 28, 47},
  {54, 32, 52},
  {58, 36, 56},
  {63, 40, 56},
  {63, 44, 57},
  {63, 49, 58},
  {63, 53, 60},
  {7, 0, 22},
  {11, 0, 25},
  {15, 0, 28},
  {20, 3, 32},
  {24, 8, 36},
  {28, 12, 41},
  {32, 16, 45},
  {36, 20, 49},
  {41, 24, 53},
  {45, 29, 57},
  {49, 33, 58},
  {53, 37, 58},
  {57, 41, 58},
  {62, 45, 58},
  {63, 50, 59},
  {63, 55, 61},
  {0, 0, 27},
  {4, 0, 30},
  {8, 2, 34},
  {13, 6, 38},
  {17, 11, 42},
  {21, 15, 47},
  {25, 19, 51},
  {29, 23, 55},
  {34, 27, 59},
  {38, 32, 61},
  {42, 36, 61},
  {46, 40, 61},
  {50, 44, 61},
  {55, 48, 61},
  {59, 53, 61},
  {63, 57, 61},
  {0, 0, 25},
  {0, 2, 30},
  {1, 6, 35},
  {6, 10, 39},
  {10, 15, 43},
  {14, 19, 48},
  {18, 23, 52},
  {22, 27, 56},
  {27, 31, 60},
  {31, 36, 63},
  {35, 40, 63},
  {39, 44, 63},
  {43, 48, 63},
  {48, 52, 63},
  {52, 57, 63},
  {56, 61, 63},
  {0, 2, 19},
  {0, 6, 24},
  {0, 10, 29},
  {0, 15, 35},
  {4, 19, 39},
  {8, 23, 43},
  {13, 27, 47},
  {17, 31, 52},
  {21, 36, 56},
  {25, 40, 60},
  {29, 44, 63},
  {34, 48, 63},
  {38, 52, 63},
  {42, 57, 63},
  {46, 61, 63},
  {50, 63, 63},
  {0, 6, 9},
  {0, 10, 14},
  {0, 14, 20},
  {0, 19, 25},
  {1, 23, 30},
  {5, 27, 34},
  {9, 31, 39},
  {14, 35, 43},
  {18, 40, 47},
  {22, 44, 51},
  {26, 48, 55},
  {30, 52, 60},
  {35, 56, 63},
  {39, 61, 63},
  {43, 63, 63},
  {47, 63, 63},
  {0, 9, 2},
  {0, 13, 3},
  {0, 17, 8},
  {0, 21, 13},
  {1, 25, 19},
  {5, 29, 23},
  {9, 34, 27},
  {13, 38, 31},
  {18, 42, 35},
  {22, 46, 40},
  {26, 50, 44},
  {30, 55, 48},
  {34, 59, 52},
  {39, 63, 56},
  {43, 63, 59},
  {47, 63, 62},
  {0, 9, 3},
  {0, 13, 4},
  {1, 17, 4},
  {0, 22, 6},
  {3, 26, 6},
  {8, 30, 10},
  {12, 34, 15},
  {16, 39, 19},
  {20, 43, 23},
  {24, 47, 27},
  {29, 51, 31},
  {33, 55, 36},
  {37, 60, 40},
  {41, 63, 44},
  {45, 63, 47},
  {50, 63, 50},
  {0, 8, 2},
  {0, 13, 3},
  {0, 17, 4},
  {5, 21, 4},
  {9, 25, 4},
  {13, 29, 4},
  {17, 33, 4},
  {21, 38, 9},
  {26, 42, 13},
  {30, 46, 17},
  {34, 50, 21},
  {38, 54, 25},
  {42, 59, 30},
  {47, 63, 34},
  {51, 63, 37},
  {55, 63, 40},
  {0, 5, 1},
  {3, 9, 1},
  {7, 14, 1},
  {11, 18, 1},
  {16, 22, 1},
  {20, 26, 1},
  {24, 30, 1},
  {28, 35, 3},
  {32, 39, 7},
  {37, 43, 11},
  {41, 47, 15},
  {45, 51, 20},
  {49, 56, 24},
  {53, 60, 28},
  {58, 63, 32},
  {62, 63, 35},
  {6, 1, 0},
  {10, 5, 0},
  {14, 10, 0},
  {19, 14, 0},
  {23, 18, 0},
  {27, 23, 0},
  {31, 27, 0},
  {36, 31, 2},
  {40, 36, 6},
  {43, 39, 10},
  {49, 44, 15},
  {53, 48, 19},
  {57, 53, 23},
  {60, 56, 27},
  {63, 61, 32},
  {63, 63, 37},
};
