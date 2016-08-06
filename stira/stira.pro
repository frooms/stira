SUBDIRS += common \
           imagedata \
           histogram \
           imagetools \
           diffusion \
           fouriertools \
           filter \
           wavelet \
           imageanalysis \
           contrastenhance \
           steerable \
           pyramidapplications \
           deconvolve \
           registration \
           degradationestimation 

TEMPLATE = subdirs

CONFIG += warn_on \
          qt \
          thread
