﻿---
layout: post
title: '图像库stb_image & stb_image_write'
date: 2019-02-24
author: Joke-Lin
tags: Tool
---

> Gitub README阅读笔记

# stb_image & stb_image_write

> Github: https://github.com/nothings/stb/

## stb_image

> stb的库像素数据都是从左到右，从上到下存储
>
> 使用 stbi_set_flip_vertically_on_load(true); 上下翻转
>
> 使用 stbi_flip_vertically_on_write(true); 在写数据的时候翻转 （在stb_write_image中）

### - 使用库

```c
#include <...>
#define STB_IMAGE_IMPLEMENTATION	// include之前必须定义
#include "stb_image.h"
```

### - 局限

- no 12-bit-per-channel JPEG 
- no JPEGs with arithmetic coding 
- GIF always returns \*comp=4 

### - 基础用法

```c
int x,y,n;
unsigned char *data = stbi_load("filename",&x,&y,&n,0);
// filename : 文件名
// x : 图片宽 
// y : 图片高
// n : 颜色通道个数
// 最后一个为自己设置的颜色通道个数，如果非0就按照此数值读取图像
// 返回值非NULL说明导入成功
// Do Something
stbi_image_free(data);
```

#### 颜色通道

- 1： 灰度图
- 2： 灰度Alpha图
- 3： 红绿蓝三色图
- 4： 红绿蓝三色Alpha图

#### 错误信息

```const char* stbi_failure_reason()```返回错误信息字符串

- 定义 STBI_NO_FAILURE_STRINGS  避免编译这些字符串
- 定义 STBI_FAILURE_USERMSG 使错误信息更加容易阅读

#### Unicode

Windows环境下可能需要满足Unicode的文件名

`#define STBI_WINDOWS_UTF8`可以使文件名满足Unicode

也可以使用`stbiw_convert_wchar_to_utf8`将`Windows wchar_t` 转换为 `utf8`.

#### Addition

- 预编译取消对某个格式的解析 ：#define STBI_NO_PNG....
- 预编译限制只能某个格式解析 ：#define STBI_ONLY_PNG...

### Else

获取x,y位置的像素信息，data为图像指针,n为颜色通道数

data[w\*n\*x+n\*y+i] (i = 0,1,..,n-1)

作者还介绍了 SIMD支持， HDR图像支持， Iphone PNG支持

## stb_image_write

### - 使用库

```c
#include <...>
#define #define STB_IMAGE_WRITE_IMPLEMENTATION	// include之前必须定义
#include "stb_image_write.h"
```

### - 简单的使用

```c
 int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
     int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
     int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
     int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
     int stbi_write_hdr(char const *filename, int w, int h, int comp, const float *data);

```

### - Else

作者还提到了PNG压缩，可提供自己的压缩函数，还有JPG质量的参数



## 代码示例

```c
#include <iostream>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace std;

void setAlpha(int x, int y, int n, int w, int alpha, unsigned char *data) {
	data[w*n*x + y * n + n - 1] = alpha;
}

int main()
{
	const char *filepath = "demo.png";
	int w, h, n;
	unsigned char *data = stbi_load(filepath, &w, &h, &n, 0);
	if (data == NULL) {
		cout << "ERROE_FILE_NOT_LOAD" << endl;
		return -1;
	}
	else {
		cout << w << " " << h << " " << n << endl;
		// 将上半身设置为透明
		for (int i = 0; i < h / 2; i++) {
			for (int j = 0; j < w; j++) {
				setAlpha(i, j, n, w, 0, data);
			}
		}
		// 写的时候翻转
		stbi_flip_vertically_on_write(true);
		stbi_write_png("out.png", w, h, n, data, 0);
	}
        stbi_image_free(data);
	return 0;
}
```
- 原图像
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190224135232798.png)
- 处理后
  ![在这里插入图片描述](https://img-blog.csdnimg.cn/20190224135301289.png)

作者还有一个`stb_image_resize.h`支持对图像的简单放缩平移等操作