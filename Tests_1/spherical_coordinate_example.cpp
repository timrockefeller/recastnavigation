// Spherical Coordinate System Example for Recast Navigation
// This file demonstrates how to use the new spherical coordinate system support

#include <iostream>
#include "Recast.h"
#include "RecastAlloc.h"

// Example function showing how to use spherical coordinates with Recast
void exampleSphericalNavigation()
{
    std::cout << "=== Spherical Coordinate System Example ===" << std::endl;
    
    // Example 1: Basic coordinate conversion
    std::cout << "\n1. Basic Spherical to Cartesian Conversion:" << std::endl;
    
    float radius = 10.0f;
    float theta = 0.5f;  // polar angle (latitude)
    float phi = 1.0f;    // azimuthal angle (longitude)
    float cartesian[3];
    
    rcSphericalToCartesian(radius, theta, phi, cartesian);
    std::cout << "Spherical (r=" << radius << ", theta=" << theta << ", phi=" << phi << ")" << std::endl;
    std::cout << "Cartesian (x=" << cartesian[0] << ", y=" << cartesian[1] << ", z=" << cartesian[2] << ")" << std::endl;
    
    // Example 2: Back conversion
    std::cout << "\n2. Cartesian to Spherical Conversion:" << std::endl;
    
    float r_back, theta_back, phi_back;
    rcCartesianToSpherical(cartesian, r_back, theta_back, phi_back);
    std::cout << "Cartesian back to Spherical:" << std::endl;
    std::cout << "r=" << r_back << ", theta=" << theta_back << ", phi=" << phi_back << std::endl;
    
    // Example 3: Planar projection for spherical surfaces
    std::cout << "\n3. Spherical to Planar Projection:" << std::endl;
    
    float spherePoint[3] = {5.0f, 3.0f, 2.0f};
    float referencePoint[3] = {1.0f, 2.0f, 3.0f};
    float planarPoint[2];
    
    rcSphericalToPlanarProjection(spherePoint, referencePoint, planarPoint);
    std::cout << "Sphere Point: (" << spherePoint[0] << ", " << spherePoint[1] << ", " << spherePoint[2] << ")" << std::endl;
    std::cout << "Reference Point: (" << referencePoint[0] << ", " << referencePoint[1] << ", " << referencePoint[2] << ")" << std::endl;
    std::cout << "Planar Projection: (" << planarPoint[0] << ", " << planarPoint[1] << ")" << std::endl;
    
    // Example 4: Back projection
    std::cout << "\n4. Planar to Spherical Projection:" << std::endl;
    
    float spherePointBack[3];
    rcPlanarToSphericalProjection(planarPoint, referencePoint, spherePointBack);
    std::cout << "Planar back to Spherical: (" << spherePointBack[0] << ", " << spherePointBack[1] << ", " << spherePointBack[2] << ")" << std::endl;
}

// Example showing how to build navigation mesh with spherical coordinates
void exampleSphericalNavMesh()
{
    std::cout << "\n=== Spherical Navigation Mesh Example ===" << std::endl;
    
    // Create a simple context
    rcContext* ctx = new rcContext();
    
    // Example configuration for spherical navigation
    rcConfig config;
    config.cs = 0.3f;  // Cell size
    config.ch = 0.2f;  // Cell height
    config.walkableSlopeAngle = 45.0f;
    config.walkableHeight = 6;
    config.walkableClimb = 4;
    config.walkableRadius = 2;
    config.maxEdgeLen = 12;
    config.maxSimplificationError = 1.3f;
    config.minRegionArea = 8;
    config.mergeRegionArea = 20;
    config.maxVertsPerPoly = 6;
    config.detailSampleDist = 6.0f;
    config.detailSampleMaxError = 1.0f;
    
    // For spherical coordinates, we might want to adjust bounds
    // to represent a spherical surface
    config.bmin[0] = -50.0f;  // X min
    config.bmin[1] = -10.0f;  // Y min (height)
    config.bmin[2] = -50.0f;  // Z min
    config.bmax[0] = 50.0f;   // X max
    config.bmax[1] = 50.0f;   // Y max (height)
    config.bmax[2] = 50.0f;   // Z max
    
    std::cout << "Config created for spherical navigation mesh generation" << std::endl;
    std::cout << "Cell size: " << config.cs << std::endl;
    std::cout << "Bounds: [" << config.bmin[0] << ", " << config.bmin[1] << ", " << config.bmin[2] << "] to ["
              << config.bmax[0] << ", " << config.bmax[1] << ", " << config.bmax[2] << "]" << std::endl;
    
    // Note: In a real implementation, you would:
    // 1. Create a heightfield with spherical input data
    // 2. Build compact heightfield
    // 3. Build contour set
    // 4. Build polygon mesh
    // 5. Build detail mesh with spherical coordinates enabled
    
    std::cout << "\nTo use spherical coordinates in navigation mesh generation:" << std::endl;
    std::cout << "1. Prepare input geometry in spherical coordinates" << std::endl;
    std::cout << "2. Set useSphericalCoordinates=true in rcBuildPolyMeshDetail()" << std::endl;
    std::cout << "3. The system will automatically handle coordinate conversions" << std::endl;
    
    delete ctx;
}

int main()
{
    std::cout << "Recast Navigation Spherical Coordinate System Demo" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    // Demonstrate coordinate conversions
    exampleSphericalNavigation();
    
    // Demonstrate navigation mesh usage
    exampleSphericalNavMesh();
    
    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "The spherical coordinate system support allows Recast Navigation to work on spherical surfaces." << std::endl;
    std::cout << "Key features:" << std::endl;
    std::cout << "- Spherical to Cartesian coordinate conversion" << std::endl;
    std::cout << "- Cartesian to Spherical coordinate conversion" << std::endl;
    std::cout << "- Planar projection for spherical surface sampling" << std::endl;
    std::cout << "- Automatic coordinate handling in navigation mesh generation" << std::endl;
    
    return 0;
}