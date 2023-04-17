# RUN

pwd = ./linux(linux)	./(windows)

Usage ：`$run <srcName-noextension> <imageName-noextension>`

Example:`$run diffuse out` means compiling diffuse.cpp and export a file named "out.ppm"

# PUSH

pwd = ./linux(linux)	./(windows)

Usage : push

# PULL

pwd = ./linux(linux)	./(windows)

Usage : pull

---

一条射线代表一个像素的颜色，该射线对一个场景（world或者bvhworld）求色过程为：

射线r与每个hitable求交（调用hitable的函数hit）

```c++
if(没有击中任何hitable)
    //递归出口1
    return 背景色;//renderer内置变量
else{
	得到命中记录rec;
    if(击中的是光源)
        //递归出口2
        return emitted = rec.mat.tex.value(rec.u,rec.v);//根据rec.u，rec.v对rec.mat_ptr.texture进行采样
    else if(击中的是可以反弹射线的物体)
    	emitted = ... //普通物体也可能发光
        scatted = rec.mat.scatter(r,rec);//使用入射光线和击中点法向量，根据具体的mat的算法得到反射光线的方向，再组合rec.pos即击中点的坐标得到反射光线的完整定义
    	attenuation = rec.mat.tex.value(rec.u,rec.v)//使用材质的固有纹理和rec的u,v坐标着色
        return emitted + attenuation * ray_color(scatted);//用反射的光线递归着色，系数为固有着色结果
}
```

返回一个hit_record类型的rec（rec中包括了击中点的三维坐标，命中的时间，法向量，命中点的材质，命中点的uv纹理坐标），该点的着色