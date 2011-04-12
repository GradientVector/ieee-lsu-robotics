
Mat GrayImage::getGI(int color)
{
  switch (color)
  {
    case 1: return getRedPixels();
            break;
    case 2: return getGreenPixels(); 	
	    break;
    case 3: return getBluePixels();
	    break;
    case 4: return getYellowPixels();
	    break;
    case 5: return getLines();
	    break;
  }
  return img;
}

Mat GrayImage::getRedPixels()
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[2], planes[1], adj);
  subtract(adj, planes[0], adj);
  return adj;
}

Mat GrayImage::getGreenPixels()
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[1], planes[2], adj);
  subtract(adj, planes[0], adj);
  return adj;
}

Mat GrayImage::getBluePixels()
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[0], planes[1], adj);
  subtract(adj, planes[2], adj);
  return adj;
}

Mat GrayImage::getYellowPixels()
{
  split(img, planes);
  Mat adj(img.rows, img.cols, CV_8UC1);
  subtract(planes[1], planes[2], adj);
  add(adj, planes[0], adj);
  subtract(adj, planes[2], adj);
  return adj;
}

Mat GrayImage::getLines()
{
  Mat adj(img.rows, img.cols, CV_8UC1);
  Mat gray;
  cvtColor(img, gray, CV_BGR2GRAY);
  subtract(adj, gray, adj);
  //line detection code here, otherwise just returns inverted grayscale
  return adj;
}
