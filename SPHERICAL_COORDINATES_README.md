# Recast Navigation 球面坐标系支持

此文档描述了如何启用和使用 Recast Navigation 库的球面坐标系支持功能。

## 功能概述

球面坐标系支持允许 Recast Navigation 在球形表面上生成导航网格，这对于行星、球体或其他曲面导航场景非常有用。

## 主要修改

### 1. 坐标转换函数 (Recast.h)

在 `Recast.h` 头文件中添加了以下球面坐标系转换函数：

```cpp
// 球面坐标到笛卡尔坐标转换
inline void rcSphericalToCartesian(float radius, float theta, float phi, float* cartesian);

// 笛卡尔坐标到球面坐标转换
inline void rcCartesianToSpherical(const float* cartesian, float& radius, float& theta, float& phi);

// 球面点到切平面投影
inline void rcSphericalToPlanarProjection(const float* spherePoint, const float* referencePoint, float* planarPoint);

// 切平面到球面投影
inline void rcPlanarToSphericalProjection(const float* planarPoint, const float* referencePoint, float* spherePoint);
```

### 2. 构建函数修改 (RecastMeshDetail.cpp)

修改了 `buildPolyDetail` 和 `rcBuildPolyMeshDetail` 函数，添加了球面坐标系支持：

```cpp
// 修改后的函数签名
bool buildPolyDetail(rcContext* ctx, const float* in, const int nin,
                     const float sampleDist, const float sampleMaxError,
                     const int heightSearchRadius, const rcCompactHeightfield& chf,
                     const rcHeightPatch& hp, float* verts, int& nverts,
                     rcIntArray& tris, rcIntArray& edges, rcIntArray& samples,
                     bool useSphericalCoordinates = false);

bool rcBuildPolyMeshDetail(rcContext* ctx, const rcPolyMesh& mesh, const rcCompactHeightfield& chf,
                           const float sampleDist, const float sampleMaxError,
                           rcPolyMeshDetail& dmesh, bool useSphericalCoordinates);
```

## 使用方法

### 启用球面坐标系

在构建细节网格时，只需将 `useSphericalCoordinates` 参数设置为 `true`：

```cpp
rcContext ctx;
rcPolyMesh mesh;
rcCompactHeightfield chf;
rcPolyMeshDetail dmesh;

// 启用球面坐标系
bool success = rcBuildPolyMeshDetail(&ctx, mesh, chf, 6.0f, 1.0f, dmesh, true);
```

### 向后兼容性

原有的函数签名仍然可用，默认使用笛卡尔坐标系：

```cpp
// 默认使用笛卡尔坐标系
bool success = rcBuildPolyMeshDetail(&ctx, mesh, chf, 6.0f, 1.0f, dmesh);
```

## 技术实现细节

### 坐标转换流程

1. **输入处理**：输入几何体可以是球面坐标或笛卡尔坐标
2. **采样阶段**：在球面坐标系下，采样点通过切平面投影进行采样
3. **三角化阶段**：在切平面上进行三角化，然后投影回球面
4. **输出**：输出网格保持球面坐标系

### 关键算法

- **切平面投影**：使用参考点处的切平面进行局部投影
- **采样优化**：在球面表面上均匀采样，避免极点处的采样密度问题
- **边界处理**：正确处理球面边界和接缝问题

## 示例代码

参见 `spherical_coordinate_example.cpp` 文件，其中包含完整的示例代码：

```cpp
#include "Recast.h"

void example() {
    // 坐标转换示例
    float radius = 10.0f, theta = 0.5f, phi = 1.0f;
    float cartesian[3];
    rcSphericalToCartesian(radius, theta, phi, cartesian);
    
    // 导航网格构建示例
    rcContext ctx;
    rcPolyMesh mesh;
    rcCompactHeightfield chf;
    rcPolyMeshDetail dmesh;
    
    // 启用球面坐标系
    rcBuildPolyMeshDetail(&ctx, mesh, chf, 6.0f, 1.0f, dmesh, true);
}
```

## 适用场景

- 行星表面导航
- 球体游戏世界
- 曲面地形导航
- 虚拟现实中的球形环境

## 限制和注意事项

1. **性能影响**：坐标转换会增加一定的计算开销
2. **精度考虑**：在极点附近可能会有精度损失
3. **边界处理**：需要特别注意球面边界和接缝的处理
4. **采样密度**：在球面表面需要均匀采样策略

## 测试验证

建议在使用前进行以下测试：

1. 基本坐标转换测试
2. 简单球面几何体的导航网格生成
3. 边界情况和极端条件的测试

## 贡献

此功能由 AI 助手实现，如需改进或修复问题，请参考源代码修改记录。

## 许可证

此修改遵循 Recast Navigation 的原始许可证条款。