///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017, Carnegie Mellon University and University of Cambridge,
// all rights reserved.
//
// ACADEMIC OR NON-PROFIT ORGANIZATION NONCOMMERCIAL RESEARCH USE ONLY
//
// BY USING OR DOWNLOADING THE SOFTWARE, YOU ARE AGREEING TO THE TERMS OF THIS
// LICENSE AGREEMENT. IF YOU DO NOT AGREE WITH THESE TERMS, YOU MAY NOT USE OR
// DOWNLOAD THE SOFTWARE.
//
// License can be found in OpenFace-license.txt
//
//     * Any publications arising from the use of this software, including but
//       not limited to academic journal and conference publications, technical
//       reports and manuals, must cite at least one of the following works:
//
//       OpenFace 2.0: Facial Behavior Analysis Toolkit
//       Tadas Baltrušaitis, Amir Zadeh, Yao Chong Lim, and Louis-Philippe
//       Morency in IEEE International Conference on Automatic Face and Gesture
//       Recognition, 2018
//
//       Convolutional experts constrained local model for facial landmark
//       detection. A. Zadeh, T. Baltrušaitis, and Louis-Philippe Morency, in
//       Computer Vision and Pattern Recognition Workshops, 2017.
//
//       Rendering of Eyes for Eye-Shape Registration and Gaze Estimation
//       Erroll Wood, Tadas Baltrušaitis, Xucong Zhang, Yusuke Sugano, Peter
//       Robinson, and Andreas Bulling in IEEE International. Conference on
//       Computer Vision (ICCV),  2015
//
//       Cross-dataset learning and person-specific normalisation for automatic
//       Action Unit detection Tadas Baltrušaitis, Marwa Mahmoud, and Peter
//       Robinson in Facial Expression Recognition and Analysis Challenge, IEEE
//       International Conference on Automatic Face and Gesture Recognition,
//       2015
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SVM_STATIC_LIN_H
#define SVM_STATIC_LIN_H

#include <string>
#include <vector>

#include <fstream>
#include <iostream>
#include <stdio.h>

#include <opencv2/core/core.hpp>

namespace FaceAnalysis {

// Collection of linear SVR regressors for AU prediction
class SVM_static_lin {

public:
  SVM_static_lin() {}

  // Predict the AU from HOG appearance of the face
  void Predict(std::vector<double> &predictions,
               std::vector<std::string> &names,
               const cv::Mat_<double> &fhog_descriptor,
               const cv::Mat_<double> &geom_params);

  // Reading in the model (or adding to it)
  void Read(std::ifstream &stream, const std::vector<std::string> &au_names);

  std::vector<std::string> GetAUNames() const { return AU_names; }

private:
  // The names of Action Units this model is responsible for
  std::vector<std::string> AU_names;

  // For normalisation
  cv::Mat_<double> means;

  // For actual prediction
  cv::Mat_<double> support_vectors;
  cv::Mat_<double> biases;

  std::vector<double> pos_classes;
  std::vector<double> neg_classes;
};
//===========================================================================
} // namespace FaceAnalysis
#endif // SVM_STATIC_LIN_H
