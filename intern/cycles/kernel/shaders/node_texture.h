/*
 * Copyright 2011-2013 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "vector2.h"
#include "vector4.h"

#define vector3 point

/* Safe versions of unsigned perlin noise. Noise can be infinit at large coordinates.
 * The noise approachs 0.5 at large coordinates.
 */

float safe_noise(float p)
{
  float f = noise("noise", p);
  if (isinf(f))
    return 0.5;
  return f;
}

float safe_noise(vector2 p)
{
  float f = noise("noise", p.x, p.y);
  if (isinf(f))
    return 0.5;
  return f;
}

float safe_noise(vector3 p)
{
  float f = noise("noise", p);
  if (isinf(f))
    return 0.5;
  return f;
}

float safe_noise(vector4 p)
{
  float f = noise("noise", vector3(p.x, p.y, p.z), p.w);
  if (isinf(f))
    return 0.5;
  return f;
}

/* Safe versions of signed perlin noise. Noise can be infinit at large coordinates.
 * The noise approachs 0.0 at large coordinates.
 */

float safe_snoise(float p)
{
  float f = noise("snoise", p);
  if (isinf(f))
    return 0.0;
  return f;
}

float safe_snoise(vector2 p)
{
  float f = noise("snoise", p.x, p.y);
  if (isinf(f))
    return 0.0;
  return f;
}

float safe_snoise(vector3 p)
{
  float f = noise("snoise", p);
  if (isinf(f))
    return 0.0;
  return f;
}

float safe_snoise(vector4 p)
{
  float f = noise("snoise", vector3(p.x, p.y, p.z), p.w);
  if (isinf(f))
    return 0.0;
  return f;
}

/* The following 4 functions are exactly the same but with different input type.
 * When refactoring, simply copy the function body to the rest of the functions.
 */

float noise_turbulence(float p, float details)
{
  float fscale = 1.0;
  float amp = 1.0;
  float sum = 0.0;
  float octaves = clamp(details, 0.0, 16.0);
  int n = (int)octaves;
  for (int i = 0; i <= n; i++) {
    float t = safe_noise(fscale * p);
    sum += t * amp;
    amp *= 0.5;
    fscale *= 2.0;
  }
  float rmd = octaves - floor(octaves);
  if (rmd != 0.0) {
    float t = safe_noise(fscale * p);
    float sum2 = sum + t * amp;
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    sum2 *= ((float)(1 << (n + 1)) / (float)((1 << (n + 2)) - 1));
    return (1.0 - rmd) * sum + rmd * sum2;
  }
  else {
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    return sum;
  }
}

float noise_turbulence(vector2 p, float details)
{
  float fscale = 1.0;
  float amp = 1.0;
  float sum = 0.0;
  float octaves = clamp(details, 0.0, 16.0);
  int n = (int)octaves;
  for (int i = 0; i <= n; i++) {
    float t = safe_noise(fscale * p);
    sum += t * amp;
    amp *= 0.5;
    fscale *= 2.0;
  }
  float rmd = octaves - floor(octaves);
  if (rmd != 0.0) {
    float t = safe_noise(fscale * p);
    float sum2 = sum + t * amp;
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    sum2 *= ((float)(1 << (n + 1)) / (float)((1 << (n + 2)) - 1));
    return (1.0 - rmd) * sum + rmd * sum2;
  }
  else {
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    return sum;
  }
}

float noise_turbulence(vector3 p, float details)
{
  float fscale = 1.0;
  float amp = 1.0;
  float sum = 0.0;
  float octaves = clamp(details, 0.0, 16.0);
  int n = (int)octaves;
  for (int i = 0; i <= n; i++) {
    float t = safe_noise(fscale * p);
    sum += t * amp;
    amp *= 0.5;
    fscale *= 2.0;
  }
  float rmd = octaves - floor(octaves);
  if (rmd != 0.0) {
    float t = safe_noise(fscale * p);
    float sum2 = sum + t * amp;
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    sum2 *= ((float)(1 << (n + 1)) / (float)((1 << (n + 2)) - 1));
    return (1.0 - rmd) * sum + rmd * sum2;
  }
  else {
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    return sum;
  }
}

float noise_turbulence(vector4 p, float details)
{
  float fscale = 1.0;
  float amp = 1.0;
  float sum = 0.0;
  float octaves = clamp(details, 0.0, 16.0);
  int n = (int)octaves;
  for (int i = 0; i <= n; i++) {
    float t = safe_noise(fscale * p);
    sum += t * amp;
    amp *= 0.5;
    fscale *= 2.0;
  }
  float rmd = octaves - floor(octaves);
  if (rmd != 0.0) {
    float t = safe_noise(fscale * p);
    float sum2 = sum + t * amp;
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    sum2 *= ((float)(1 << (n + 1)) / (float)((1 << (n + 2)) - 1));
    return (1.0 - rmd) * sum + rmd * sum2;
  }
  else {
    sum *= ((float)(1 << n) / (float)((1 << (n + 1)) - 1));
    return sum;
  }
}
