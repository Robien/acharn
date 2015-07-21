#ifndef SHADERCALLBACK_H_INCLUDED
#define SHADERCALLBACK_H_INCLUDED
#include "../include/Referenced.h"

class ShaderCallBack: public video::IShaderConstantSetCallBack, public Referenced
{
public:

    ShaderCallBack(IrrlichtDevice* _device)
    {
        device = _device;
    }

    virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
    {

        video::IVideoDriver* driver = services->getVideoDriver();

        // Set inverted world matrix
        // if we are using highlevel shaders (the user can select this when
        // starting the program), we must set the constants by name.
        core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
        invWorld.makeInverse();
        services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);

        // Set clip matrix
        core::matrix4 worldViewProj;
        worldViewProj = driver->getTransform(video::ETS_PROJECTION);
        worldViewProj *= driver->getTransform(video::ETS_VIEW);
        worldViewProj *= driver->getTransform(video::ETS_WORLD);
        services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);

        // Set camera position
        core::vector3df pos = device->getSceneManager()->getActiveCamera()->getAbsolutePosition();
        services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*> (&pos), 3);

        // Set light color
        video::SColorf col(0.0f, 1.0f, 1.0f, 0.0f);
        services->setVertexShaderConstant("mLightColor", reinterpret_cast<f32*> (&col), 4);

        // Set transposed world matrix
        core::matrix4 world = driver->getTransform(video::ETS_WORLD);
        world = world.getTransposed();
        services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);

        // set timer
        f32 time = device->getTimer()->getTime();
        services->setVertexShaderConstant("Timer", &time, 1);
        services->setPixelShaderConstant("Timer", &time, 1);

        // set textures
        int a = 0;
        services->setPixelShaderConstant("Texture1", (const float*) &a, 1);
        a = 1;
        services->setPixelShaderConstant("Texture2", (const float*) &a, 1);
        a = 2;
        services->setPixelShaderConstant("Texture3", (const float*) &a, 1);
        a = 3;
        services->setPixelShaderConstant("Texture4", (const float*) &a, 1);

    }

private:

    IrrlichtDevice* device;
};

#endif // SHADERCALLBACK_H_INCLUDED
