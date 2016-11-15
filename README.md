# CUDA Wndchrm

## Background

  Image processing is increasing in demand every year as our technology produces images in higher resolution and higher volumes. This demand arises from both consumer and scientific sources alike. The volume of data produced increases steadily however the methods to deal with it are limiting its usefulness.
  
## Methods
  
  CUDA Wndchrm is an open source re-implementation of select algorithms from [`wndchrm`](http://scfbm.biomedcentral.com/articles/10.1186/1751-0473-3-13). They are modified and structured in a way that they may be executed on Nvidia's CUDA enabled devices to employ parallel computing and speed up the process of image analysis. The algorithms selected are those that are the most time consuming to reduce image processing time as much as possible.
  
## Results

  The modified algorithms are tested against the results of the [original implementation](http://scfbm.biomedcentral.com/articles/10.1186/1751-0473-3-13). Of interest is the accuracy of the algorithms, compared to the ones found in [wndchrm](http://scfbm.biomedcentral.com/articles/10.1186/1751-0473-3-13) as well as a quantified measure of improvement in speed. CUDA Wndchrm also aims to maintain a simple interface so that anyone can take advantage of its bulk image processing capabilities.
  
## Conclusion

  CUDA Wndchrm can be freely used to perform computationaly expensive image processing on widely available, cheap consumer-grade GPUs to improve processing speed significantly. It is suggested for use on large datasets that would otherwise take impractical amounts of time to compute. 
