
enum Direction
{
    Direction_North = 0,
    Direction_NorthEast,
    Direction_SouthEast,
    Direction_South,
    Direction_SouthWest,
    Direction_NorthWest,

    Direction_Count
};

enum Terrain
{
    Terrain_Plains = 0,
    Terrain_Desert,
    Terrain_Mountain,
    Terrain_Swamp,
    Terrain_Forest,

    Terrain_Count
};

struct Tile
{
    int id;
    int adjacent_id[Direction_Count];
    Terrain terrain;
    int led_index;
    int led_count;
};

Direction clockwise(Direction in);
Direction counter_clockwise(Direction in);

static const int num_tiles = 94;
static Tile tiles[num_tiles] = {
    { 0, { 4,  1, -1, -1, -1, -1}, Terrain_Swamp,  130, 2},
    { 1, { 5,  2, -1, -1,  0,  4}, Terrain_Plains, 132, 2},
    { 2, { 6,  3, -1, -1,  1,  5}, Terrain_Plains, 168, 2},
    { 3, { 7, -1, -1, -1,  2,  6}, Terrain_Plains, 170, 2},
    { 4, {12,  5,  1,  0, -1, 11}, Terrain_Plains, 128, 2},
    { 5, {13,  6,  2,  1,  4, 12}, Terrain_Plains, 134, 2},
    { 6, {14,  7,  3,  2,  5, 13}, Terrain_Plains, 166, 2},
    { 7, {15,  8, -1,  3,  6, 14}, Terrain_Plains, 172, 2},
    { 8, {-1, -1, -1, -1,  7, 15}, Terrain_Plains, 176, 2},
    { 9, {17, -1, -1, -1, -1, 16}, Terrain_Plains,  74, 2},
    {10, {19, 11, -1, -1, -1, 18}, Terrain_Plains,  86, 1},
    {11, {20, 12,  4, -1, 10, 19}, Terrain_Plains,  87, 2},
    {12, {21, 13,  5,  4, 11, 20}, Terrain_Plains, 126, 2},
    {13, {22, 14,  6,  5, 12, 21}, Terrain_Plains, 136, 2},
    {14, {23, 15,  7,  6, 13, 22}, Terrain_Plains, 164, 2},
    {15, {-1, -1,  8,  7, 14, 23}, Terrain_Plains, 174, 2},
    {16, {25, 17,  9, -1, -1, 24}, Terrain_Plains,  34, 2},
    {17, {26, 18, -1,  9, 16, 25}, Terrain_Plains,  72, 2},
    {18, {27, 19, 10, -1, 17, 26}, Terrain_Plains,  76, 2},
    {19, {28, 20, 11, 10, 18, 27}, Terrain_Plains,  84, 2},
    {20, {29, 21, 12, 11, 19, 28}, Terrain_Plains,  89, 2},
    {21, {30, 22, 13, 12, 20, 29}, Terrain_Plains, 124, 2},
    {22, {31, 23, 14, 13, 21, 30}, Terrain_Plains, 138, 2},
    {23, {32, -1, 15, 14, 22, 31}, Terrain_Plains, 162, 2},
    {24, {34, 25, 16, -1, -1, 33}, Terrain_Plains,  32, 2},
    {25, {35, 26, 17, 16, 24, 34}, Terrain_Plains,  36, 2},
    {26, {36, 27, 18, 17, 25, 35}, Terrain_Plains,  70, 2},
    {27, {37, 28, 19, 18, 26, 36}, Terrain_Plains,  78, 2},
    {28, {-1, 29, 20, 19, 27, 37}, Terrain_Plains,  82, 2},
    {29, {-1, 30, 21, 20, 28, -1}, Terrain_Plains,  91, 2},
    {30, {38, 31, 22, 21, 29, -1}, Terrain_Plains, 122, 2},
    {31, {39, 32, 23, 22, 30, 38}, Terrain_Plains, 140, 2},
    {32, {40, -1, -1, 23, 31, 39}, Terrain_Plains, 160, 2},
    {33, {43, 34, 24, -1, -1, -1}, Terrain_Plains,   2, 2},
    {34, {44, 35, 25, 24, 33, 43}, Terrain_Plains,  30, 2},
    {35, {45, 36, 26, 25, 34, 44}, Terrain_Plains,  38, 2},
    {36, {46, 37, 27, 26, 35, 45}, Terrain_Plains,  68, 2},
    {37, {-1, -1, 28, 27, 36, 46}, Terrain_Plains,  80, 2},
    {38, {47, 39, 31, 30, -1, -1}, Terrain_Plains, 120, 2},
    {39, {48, 40, 32, 31, 38, 47}, Terrain_Plains, 142, 2},
    {40, {49, 41, -1, 32, 39, 48}, Terrain_Plains, 158, 2},
    {41, {50, 42, -1, -1, 40, 49}, Terrain_Plains, 178, 2},
    {42, {-1, -1, -1, -1, 41, 50}, Terrain_Plains, 184, 2},
    {43, {52, 44, 34, 33, -1, 51}, Terrain_Plains,   4, 2},
    {44, {53, 45, 35, 34, 43, 52}, Terrain_Plains,  28, 2},
    {45, {54, 46, 36, 35, 44, 53}, Terrain_Plains,  40, 2},
    {46, {55, -1, 37, 36, 45, 54}, Terrain_Plains,  66, 2},
    {47, {57, 48, 39, 38, -1, 56}, Terrain_Plains, 118, 2},
    {48, {58, 49, 40, 39, 47, 57}, Terrain_Plains, 144, 2},
    {49, {59, 50, 41, 40, 48, 58}, Terrain_Plains, 156, 2},
    {50, {60, -1, 42, 41, 49, 59}, Terrain_Plains, 180, 2},
    {51, {-1, 52, 43, -1, -1, -1}, Terrain_Plains,   0, 2},
    {52, {-1, 53, 44, 43, 51, -1}, Terrain_Plains,   6, 2},
    {53, {61, 54, 45, 44, 52, -1}, Terrain_Plains,  26, 2},
    {54, {62, 55, 46, 45, 53, 61}, Terrain_Plains,  42, 2},
    {55, {63, -1, -1, 46, 54, 62}, Terrain_Plains,  64, 2},
    {56, {66, 57, 47, -1, -1, 65}, Terrain_Plains, 104, 2},
    {57, {67, 58, 48, 47, 56, 66}, Terrain_Plains, 116, 2},
    {58, {68, 59, 49, 48, 57, 67}, Terrain_Plains, 146, 2},
    {59, {69, 60, 50, 49, 58, 68}, Terrain_Plains, 154, 2},
    {60, {-1, -1, -1, 50, 59, 69}, Terrain_Plains, 182, 2},
    {61, {70, 62, 54, 53, -1, -1}, Terrain_Plains,  24, 2},
    {62, {71, 63, 55, 54, 61, 70}, Terrain_Plains,  44, 2},
    {63, {72, 64, -1, 55, 62, 71}, Terrain_Plains,  62, 2},
    {64, {73, 65, -1, -1, 63, 72}, Terrain_Plains,  93, 2},
    {65, {74, 66, 56, -1, 64, 73}, Terrain_Plains, 102, 2},
    {66, {75, 67, 57, 56, 65, 74}, Terrain_Plains, 106, 2},
    {67, {76, 68, 58, 57, 66, 75}, Terrain_Plains, 114, 2},
    {68, {77, 69, 59, 58, 67, 76}, Terrain_Plains, 148, 2},
    {69, {-1, -1, 60, 59, 68, 77}, Terrain_Plains, 152, 2},
    {70, {79, 71, 62, 61, -1, 78}, Terrain_Plains,  22, 2},
    {71, {80, 72, 63, 62, 70, 79}, Terrain_Plains,  46, 2},
    {72, {81, 73, 64, 63, 71, 80}, Terrain_Plains,  60, 2},
    {73, {82, 74, 65, 64, 72, 81}, Terrain_Plains,  95, 2},
    {74, {83, 75, 66, 65, 73, 82}, Terrain_Plains, 100, 2},
    {75, {-1, 76, 67, 66, 74, 83}, Terrain_Plains, 108, 2},
    {76, {84, 77, 68, 67, 75, -1}, Terrain_Plains, 112, 2},
    {77, {-1, -1, 69, 68, 76, 84}, Terrain_Plains, 150, 2},
    {78, {86, 79, 70, -1, -1, 85}, Terrain_Plains,  10, 2},
    {79, {87, 80, 71, 70, 78, 86}, Terrain_Plains,  20, 2},
    {80, {88, 81, 72, 71, 79, 87}, Terrain_Plains,  48, 2},
    {81, {89, 82, 73, 72, 80, 88}, Terrain_Plains,  58, 2},
    {82, {-1, 83, 74, 73, 81, 89}, Terrain_Plains,  97, 2},
    {83, {-1, -1, 75, 74, 82, -1}, Terrain_Plains,  99, 1},
    {84, {-1, -1, 77, 76, -1, -1}, Terrain_Plains, 110, 2},
    {85, {-1, 86, 78, -1, -1, -1}, Terrain_Plains,   8, 2},
    {86, {90, 87, 79, 78, 85, -1}, Terrain_Plains,  12, 2},
    {87, {91, 88, 80, 79, 86, 90}, Terrain_Plains,  18, 2},
    {88, {92, 89, 81, 80, 87, 91}, Terrain_Plains,  50, 2},
    {89, {93, -1, 82, 81, 88, 92}, Terrain_Plains,  56, 2},
    {90, {-1, 91, 87, 86, -1, -1}, Terrain_Plains,  14, 2},
    {91, {-1, 92, 88, 87, 90, -1}, Terrain_Plains,  16, 2},
    {92, {-1, 93, 89, 88, 91, -1}, Terrain_Plains,  52, 2},
    {93, {-1, -1, -1, 89, 92, -1}, Terrain_Plains,  54, 2},
};

Tile* get_tile(int id);

