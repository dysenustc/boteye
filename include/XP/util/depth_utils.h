/******************************************************************************
 * Copyright 2017 Baidu Robotic Vision Authors. All Rights Reserved.
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
 *****************************************************************************/

#ifndef XP_UTIL_DEPTH_UTILS_H_
#define XP_UTIL_DEPTH_UTILS_H_

#include <XP/helper/param.h>
namespace XP {
bool multilevel_stereoBM(const DuoCalibParam& duo_calib_param,
                         const cv::Mat& l_img,
                         const cv::Mat& r_img,
                         cv::Mat* disparity_ptr,
                         std::vector<cv::Mat>* disparity_ml_ptr,
                         int start_level = 0,  // set to higher level to reduce time
                         int end_level = 4);

inline cv::Vec3b depth16S2color(int16_t depth) {
  // 255 / 16 ~= 16
  // opencv disparity result in 16S is multiplied by 16
  int val = depth * 8 / 16;
  if (val <= 0) {
    return cv::Vec3b(0, 0, 0);
  }
  if (val > 255) val = 255;
  uchar r = 0, g = 0, b = 0;
  if (val > 128) {
    r = (val - 128) * 2;
    b = (255 - val) * 2;
  } else {
    b = (val) * 2;
    g = (128 - val) * 2;
  }
  return cv::Vec3b(b, g, r);
}
} // namespace XP
#endif  // XP_UTIL_DEPTH_UTILS_H_