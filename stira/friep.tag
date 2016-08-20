<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>stira::filter::AdaptiveBilateralFilter</name>
    <filename>classstira_1_1filter_1_1AdaptiveBilateralFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>AdaptiveBilateralFilter</name>
      <anchorfile>classstira_1_1filter_1_1AdaptiveBilateralFilter.html</anchorfile>
      <anchor>afb76146693d9becdaa02634afed6747f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdaptiveBilateralFilter</name>
      <anchorfile>classstira_1_1filter_1_1AdaptiveBilateralFilter.html</anchorfile>
      <anchor>a88d38c0b68e7679658cf40077bacdcaf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1AdaptiveBilateralFilter.html</anchorfile>
      <anchor>a53c24938ab8c6ce131bb3250b278414b</anchor>
      <arglist>(Image *pImage)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::contrastenhance::AdaptiveEnhanceLuong</name>
    <filename>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</filename>
    <member kind="function">
      <type></type>
      <name>AdaptiveEnhanceLuong</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</anchorfile>
      <anchor>ad9854cc0644c6c109e3d8e9489cd843f</anchor>
      <arglist>(int windowSize=9)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdaptiveEnhanceLuong</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</anchorfile>
      <anchor>abd28fcd6aa15f786a43dd17593f92a04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</anchorfile>
      <anchor>ac86b1e47b724e45b1b23d07ef7cb140b</anchor>
      <arglist>(Image *pSourceImage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAlphaFactor</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</anchorfile>
      <anchor>ad2495d8992996895cc4b46f7fbe0e31e</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetWindowSize</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveEnhanceLuong.html</anchorfile>
      <anchor>a45641fd353abef3ebaa8eef7ff88bbcf</anchor>
      <arglist>(int size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::contrastenhance::AdaptiveHistogramEqualizer</name>
    <filename>classstira_1_1contrastenhance_1_1AdaptiveHistogramEqualizer.html</filename>
    <member kind="function">
      <type></type>
      <name>AdaptiveHistogramEqualizer</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveHistogramEqualizer.html</anchorfile>
      <anchor>a05fc8841c35c4273e864bc9a2ed7250f</anchor>
      <arglist>(Image *pSourceImage, int blockWidth, int blockHeight)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AdaptiveHistogramEqualizer</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveHistogramEqualizer.html</anchorfile>
      <anchor>a79f358dbace859ffcfa58de944b18d44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveHistogramEqualizer.html</anchorfile>
      <anchor>a04fef3b152bba03054274b56f4a2d0dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1contrastenhance_1_1AdaptiveHistogramEqualizer.html</anchorfile>
      <anchor>af1a035c114ebf9e64ca2d790170125b2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::AffineTransform</name>
    <filename>classstira_1_1image_1_1AffineTransform.html</filename>
    <base>stira::image::GeometricTransform</base>
    <member kind="function">
      <type></type>
      <name>AffineTransform</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>ae0a1346481eddc1a8ba7168bd3c2c76f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AffineTransform</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a60a3a300ac98a482298d3b1255c342cc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA11</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a0f1094096052830654a94802ef681b0e</anchor>
      <arglist>(double a11)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetA11</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a89e68cf5d0cd5c0be894579a6a48d1a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA12</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a129650457bf3c1dbffebe836283aad1e</anchor>
      <arglist>(double a12)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetA12</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a4ebe6dcbfe7151d3b9561082c12ce417</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA21</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a20cf24045aa0e97660bce0e894f1b4f4</anchor>
      <arglist>(double a21)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetA21</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>ab46b821ec9823236a3d80f309094eb7a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA22</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a241ae9fde6360b5ed8cca5e0c693b7b7</anchor>
      <arglist>(double a22)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetA22</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a6ca7a2385ba9762651adab7e44c29e1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaX</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a7c6daf202c0d7344e62e46df4275866c</anchor>
      <arglist>(double dx)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDeltaX</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>af105697807ab1a6a58b2e94a54175dae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaY</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>aba59fe99e62ac3e0b30dedb06ad17597</anchor>
      <arglist>(double dy)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDeltaY</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a06ce02126afdee033450f5ad6fbd101b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDeterminant</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a59cbad46e476ba89784c47b1e5a472eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual common::Point&lt; double &gt;</type>
      <name>GetTransformedPoint</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>a3bf04bb2e75055b0ed6ae33cf613c089</anchor>
      <arglist>(double x, double y)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual common::Point&lt; double &gt;</type>
      <name>GetInverseTransformedPoint</name>
      <anchorfile>classstira_1_1image_1_1AffineTransform.html</anchorfile>
      <anchor>aff39df977899c8c8e2bd062f90689bcd</anchor>
      <arglist>(double x, double y)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::diffusion::AnisotropicDiffusion</name>
    <filename>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</filename>
    <member kind="function">
      <type></type>
      <name>AnisotropicDiffusion</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>aef5a404d0e9cc2787212ff1a38080ef3</anchor>
      <arglist>(Image *pSourceImage)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AnisotropicDiffusion</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>a4a95a9344a89158aeb0c0f6ddaadf34d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetFlowFactor</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>af19d8a0da8f203831b8371e09d98ad0f</anchor>
      <arglist>(double fc)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetFlowFactor</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>a56aaf46a82060073d0091c81823820eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxNumberOfIterations</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>a87d8a02fd369710bc54eebf468f13baf</anchor>
      <arglist>(int maxnr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaxNumberOfIterations</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>a8d66dbed99580597f54da41f5869b205</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1diffusion_1_1AnisotropicDiffusion.html</anchorfile>
      <anchor>af25d98f468e4d7ee497591111dec0486</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::AnisotropicGaussian</name>
    <filename>classstira_1_1filter_1_1AnisotropicGaussian.html</filename>
    <member kind="function">
      <type></type>
      <name>AnisotropicGaussian</name>
      <anchorfile>classstira_1_1filter_1_1AnisotropicGaussian.html</anchorfile>
      <anchor>a33f09346aeb5d722bba124974b9751ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AnisotropicGaussian</name>
      <anchorfile>classstira_1_1filter_1_1AnisotropicGaussian.html</anchorfile>
      <anchor>ab9264720d6162286bf7c759432d312ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1AnisotropicGaussian.html</anchorfile>
      <anchor>ac1924e0c8f7a4967c4a59931a52840a4</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput, double sigmav, double sigmau, double theta, int orderv, int orderu)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::ArrayGrid</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, T intensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, T *pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; T &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(T value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; T &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, T *pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, T *columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, T myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; T &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T *</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; bool &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, boolintensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, bool *pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; bool &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; bool &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(boolvalue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; bool &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, bool *pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, bool *columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool *</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, boolmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; bool &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool *</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; double &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, doubleintensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, double *pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; double &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double &amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(doublevalue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; double &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, double *pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, double *columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double *</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, doublemyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; double &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double *</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, histogram::stira::histogram::FloatHistogram *intensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, histogram::stira::histogram::FloatHistogram **pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram *&amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram *</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(histogram::stira::histogram::FloatHistogram *value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, histogram::stira::histogram::FloatHistogram **pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram **</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, histogram::stira::histogram::FloatHistogram **columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram **</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram *</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram *</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram **</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>histogram::stira::histogram::FloatHistogram **</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, histogram::stira::histogram::FloatHistogram *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; histogram::stira::histogram::FloatHistogram * &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>histogram::stira::histogram::FloatHistogram **</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; int &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, intintensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, int *pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; int &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; int &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int &amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(intvalue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; int &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, int *pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, int *columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int *</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, intmyValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; int &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int *</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; std::complex&lt; double &gt; &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, std::complex&lt; double &gt;intensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, std::complex&lt; double &gt; *pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; std::complex&lt; double &gt; &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(std::complex&lt; double &gt;value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; std::complex&lt; double &gt; &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, std::complex&lt; double &gt; *pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt; *</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, std::complex&lt; double &gt; *columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt; *</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt; *</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt; *</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, std::complex&lt; double &gt;myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; std::complex&lt; double &gt; &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt; *</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</filename>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a374e9f73515dc01649477af9f0d53b51</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c85969c8d158be92657db701403ee1a</anchor>
      <arglist>(int width, int height, bool needsInitialization, stira::imagedata::datastructures::LocalOrientation *intensity)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a075852507e9216e9b549c814c6fbcf91</anchor>
      <arglist>(int width, int height, stira::imagedata::datastructures::LocalOrientation **pArray)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a21e166f6fd4b85e2c996b5177f9df7d1</anchor>
      <arglist>(const ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; &amp;pArrayGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a2ae0abb322fde476796d0de5c74d0645</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a8e4bb8b45c58116ee8e2b8c6c7c0c8f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation *&amp;</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afb9dbd1492f9f7c1e14c87b6eb0a4ea1</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation *</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a32a551373596c15b25c0068f50cbb2d7</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a9e2acfdfc163fac6db40b986ba3f67ac</anchor>
      <arglist>(stira::imagedata::datastructures::LocalOrientation *value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGridValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4631680e4e479585784cd3e2da687afd</anchor>
      <arglist>(const ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; &amp;otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a64d555a918473a0081c7dce2a62b13e8</anchor>
      <arglist>(int y, stira::imagedata::datastructures::LocalOrientation **pRowBuffer)</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation **</type>
      <name>GetRowCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3aec58abbab9aab897f6f29925c0cf06</anchor>
      <arglist>(int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a49e12e5d95c1548489dfc1386cba49fa</anchor>
      <arglist>(int x, stira::imagedata::datastructures::LocalOrientation **columnBuffer)</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation **</type>
      <name>GetColumnCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a65161af97d9838475af2d84a57f2033c</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation *</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7f1b0ed437c3406c15399928a7dcdf01</anchor>
      <arglist>(int x, int y) const</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation *</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aee8291bfc62d0fe99279ea59da3c31ea</anchor>
      <arglist>(common::Point&lt; int &gt; pt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a63b19cef4917131facadcbc7c3c9a2b7</anchor>
      <arglist>(int x, int y, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4e8f8899b158d8cff2b8067d90020208</anchor>
      <arglist>(std::vector&lt; common::Point&lt; int &gt; &gt; ptVector, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0cbe8fd49c491092f9ec376c65e426f7</anchor>
      <arglist>(common::Point&lt; int &gt; pt, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a169f0115857a01956dfd7ec6d770264f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>af812090b40ca884123e2c4b4e3d5b23f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation **</type>
      <name>GetDataCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a25b3dd65400d4ffc1ba788eacc14fee5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>stira::imagedata::datastructures::LocalOrientation **</type>
      <name>GetDataPointer</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aba40894c0dc1a8f4d4e647327a9e0a5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa9d72abf94bcc6b43370468a21ebc149</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a5cf5c3e40273d8db8766b42cdd96dfc2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a0aa27b05bbb8cbfb191c7059fdf308ac</anchor>
      <arglist>(int x, int y, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOne</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a57af1f5ca7bf62ce700e91ab76d95f83</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a7aff4c9b75d60d93f2ba380dfcb9c183</anchor>
      <arglist>(int x, int y, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideValue</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aaf6a367d339d73a35dc439e23ab24e79</anchor>
      <arglist>(int x, int y, stira::imagedata::datastructures::LocalOrientation *myValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a45fb2ad073af6f6f48f877f58f12cc56</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a66f2b2c891be647b9ede11c382d03dfc</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a78e3882937fd3b9d40047454cbb354bf</anchor>
      <arglist>(ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a709b0ba88c2732cbfc0fbe67faa49701</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a3bef69cd520c2988d45d9288ca2a0979</anchor>
      <arglist>(std::complex&lt; double &gt; factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DivideBy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>ae4fd3bc5059df7dabb37565b5d25067d</anchor>
      <arglist>(ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aa5b800cea35701f10ede460131c2c168</anchor>
      <arglist>(ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SubtractGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a4c11407155dd93653e4e72887b755825</anchor>
      <arglist>(ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; *otherGrid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>CreateGridCopy</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>afd0def82750f8e101a350f279622accd</anchor>
      <arglist>(const ArrayGrid&lt; stira::imagedata::datastructures::LocalOrientation * &gt; &amp;otherArrayGrid)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>stira::imagedata::datastructures::LocalOrientation **</type>
      <name>mpArrayGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>aeee338e24f72d70b8e57091dce376ca0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a6217e90c8369d25ac2c80a0ac1c770c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1ArrayGrid.html</anchorfile>
      <anchor>a94d323ec6df654e8760a792f8056a86e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::simpletools::ArrayGridTools</name>
    <filename>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>ArrayGridTools</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a228bd1a17b0ab8592c0429548825aa80</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ArrayGridTools</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>ab985a9a46d93f7f09a88682464ee4809</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>DownSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a3bba99f649f2f983efe175ffc0813a5a</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>UpSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a7d200c67d7288767c8d92913d045fa1f</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, int upSampledWidth, int upSampledHeight, double myFactor=4.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>CreateGridFromArray</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>aed82dc07a03e43c969154646d62e206c</anchor>
      <arglist>(T *pArray, int width, int height)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>CreateArrayFromGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a9694263522cc85d8729d3d5659d79fd1</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>ExtractSubGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a236ddff18d32233c89f2e446a30edd11</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, int xTop, int yTop, int xBottom, int yBottom)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>InsertSubGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>af4272d015757cb2dce33fd3f4d502a36</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pMasterGrid, ArrayGrid&lt; T &gt; *pSubGrid, int xTop, int yTop, int xBottom, int yBottom)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>CircularShiftGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1ArrayGridTools.html</anchorfile>
      <anchor>a7dd363ea0e054fbc643ad98e770a7059</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, int deltaX, int deltaY)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::BasicFilterKernels</name>
    <filename>classstira_1_1steerable_1_1BasicFilterKernels.html</filename>
    <member kind="function">
      <type></type>
      <name>BasicFilterKernels</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>acee1142cc93295a3224cb785ea1ce11f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BasicFilterKernels</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>aec84409cb696dd2045b22d241767b606</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>GetBasicfilterLength</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a4af8c0942f1504b9f62caa1f69598758</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterG2F1</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a02ad092518c8d7fe0ad9048e810a8829</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterG2F2</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a1b0c986f3310bef7741c3f51239d00f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterG2F3</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a559ddfdd8347b05547d22525884dfafd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterH2F1</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a0741c5e21e3a1702bc8fe8c15e45320a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterH2F2</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>aa9db1b840eef96e529a8458424be76f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterH2F3</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a8f4b364471d60243e62adc1207836cc4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetFilterH2F4</name>
      <anchorfile>classstira_1_1steerable_1_1BasicFilterKernels.html</anchorfile>
      <anchor>a9bca7b1ed604125b2c9a3a37dc0c7c3e</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::BicubicInterpolator</name>
    <filename>classstira_1_1image_1_1BicubicInterpolator.html</filename>
    <base>stira::image::Interpolator</base>
    <member kind="function">
      <type></type>
      <name>BicubicInterpolator</name>
      <anchorfile>classstira_1_1image_1_1BicubicInterpolator.html</anchorfile>
      <anchor>a7c43679ae80c6922daeaca3c40f221c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BicubicInterpolator</name>
      <anchorfile>classstira_1_1image_1_1BicubicInterpolator.html</anchorfile>
      <anchor>a8480914bd6e1236ea7e43e93d16c89cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1image_1_1BicubicInterpolator.html</anchorfile>
      <anchor>a854ea39f86c7a469301b2479469514b5</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double x, double y)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::BilinearInterpolator</name>
    <filename>classstira_1_1image_1_1BilinearInterpolator.html</filename>
    <base>stira::image::Interpolator</base>
    <member kind="function">
      <type></type>
      <name>BilinearInterpolator</name>
      <anchorfile>classstira_1_1image_1_1BilinearInterpolator.html</anchorfile>
      <anchor>afeede5121ca8116be4f49e572bb1efee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~BilinearInterpolator</name>
      <anchorfile>classstira_1_1image_1_1BilinearInterpolator.html</anchorfile>
      <anchor>afa6212450cabe5d3fb657d62f0a9525e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1image_1_1BilinearInterpolator.html</anchorfile>
      <anchor>a34fc3b12fe400557cf17fd909ac8c3ef</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double x, double y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1image_1_1BilinearInterpolator.html</anchorfile>
      <anchor>ad4bd1e85c0eec813144b737c6061ab02</anchor>
      <arglist>(double x1, double x2, double y1, double y2, double I11, double I12, double I21, double I22, double x, double y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::filter::blockMatch</name>
    <filename>structstira_1_1filter_1_1blockMatch.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>x</name>
      <anchorfile>structstira_1_1filter_1_1blockMatch.html</anchorfile>
      <anchor>afa0fc995b75aa97f10a6cb242b8820e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>y</name>
      <anchorfile>structstira_1_1filter_1_1blockMatch.html</anchorfile>
      <anchor>ade795e2feba33ee5d26385f27993776a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>distance</name>
      <anchorfile>structstira_1_1filter_1_1blockMatch.html</anchorfile>
      <anchor>a320c03a3fda3291ea8c2a426bbadee17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::degradationestimation::BlurEstimator</name>
    <filename>classstira_1_1degradationestimation_1_1BlurEstimator.html</filename>
    <member kind="function">
      <type></type>
      <name>BlurEstimator</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a8c9066b31ee534a306ffe997642566ba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BlurEstimator</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a4ffacd86813e896d8d0cfdbec0abf13b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a6bf91a20ab5e83aabd8847d7b07aea66</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBlurUnderLimit</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a0b0e8706039097d70c5f10ca899f7dae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBlurUnderLimit</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a5b18b7c11d3ff125debb05c3d2f4beda</anchor>
      <arglist>(double underLimit)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBlurUpperLimit</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>ae98db0df4ca34c2e8a25c3b6393e4862</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBlurUpperLimit</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a013e273e5ed1c1583bda7b988fe6c099</anchor>
      <arglist>(double upperLimit)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetStepSize</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a008e30e1c11ce17fe52c2ec844843083</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStepSize</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a8784790c284a8f0d93f74ab159b2bea1</anchor>
      <arglist>(double stepSize)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetNoiseLevel</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>a234af008e2b8aa94f546511e8e78367f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNoiseLevel</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimator.html</anchorfile>
      <anchor>ad1f3944a71d1a45137f9b70409e16918</anchor>
      <arglist>(double noiseLevel)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::degradationestimation::BlurEstimatorHu</name>
    <filename>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</filename>
    <member kind="function">
      <type></type>
      <name>BlurEstimatorHu</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>af4079cf1d7e34d02a7b15c616296bd27</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~BlurEstimatorHu</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>a9efdb487d594b5553d3efafa07833571</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigmaA</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>a29da5589ca5c38ec5c2c259277542ca0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigmaA</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>a95c1b0998e642a4ec722c641d38d6d8a</anchor>
      <arglist>(double sigmaA)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigmaB</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>a8ed7c53db1802c220eb7cc564568f520</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigmaB</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>aaf13137e00421c446a3b48a3d1374cc8</anchor>
      <arglist>(double sigmaB)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1degradationestimation_1_1BlurEstimatorHu.html</anchorfile>
      <anchor>aa0b6077fd14e2d23071b1de6c0ee1420</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::CannyEdgeDetector</name>
    <filename>classstira_1_1imageanalysis_1_1CannyEdgeDetector.html</filename>
    <member kind="function">
      <type></type>
      <name>CannyEdgeDetector</name>
      <anchorfile>classstira_1_1imageanalysis_1_1CannyEdgeDetector.html</anchorfile>
      <anchor>a2e6a7dcf7d15c2b2848fb4b7e80efd04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CannyEdgeDetector</name>
      <anchorfile>classstira_1_1imageanalysis_1_1CannyEdgeDetector.html</anchorfile>
      <anchor>a6108ed79ad5deefba116716aa8c68f9a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; bool &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1CannyEdgeDetector.html</anchorfile>
      <anchor>af83de755bbae0d84b2198209d0c90d69</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigmaSmooth, double lowerThreshold, double upperThreshold)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>cartesianCoord</name>
    <filename>structcartesianCoord.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::image::ChromaticAdaptation</name>
    <filename>classstira_1_1image_1_1ChromaticAdaptation.html</filename>
    <member kind="function">
      <type></type>
      <name>ChromaticAdaptation</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>afe7200fe8a1d8031f003ac68c00d9502</anchor>
      <arglist>(const ColorValue sourceReferenceWhite, const ColorValue destinationReferenceWhite, ChromaticAdaptationType myType=CHROMATICADAPTATION_BRADFORD)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ChromaticAdaptation</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>a56372abe4c06cb7ee3fdc9938b4127e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptXYZColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>af52179a6ac982e205aeaf9595721b485</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptsRGBColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>ad378bffd0f90165221fe1723f31ee169</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptLabColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>a48c000b148e60a8c3e01a028d33b6fd0</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ChromaticAdaptation</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>afe7200fe8a1d8031f003ac68c00d9502</anchor>
      <arglist>(const ColorValue sourceReferenceWhite, const ColorValue destinationReferenceWhite, ChromaticAdaptationType myType=CHROMATICADAPTATION_BRADFORD)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ChromaticAdaptation</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>a56372abe4c06cb7ee3fdc9938b4127e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptXYZColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>af52179a6ac982e205aeaf9595721b485</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptsRGBColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>ad378bffd0f90165221fe1723f31ee169</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdaptLabColor</name>
      <anchorfile>classstira_1_1image_1_1ChromaticAdaptation.html</anchorfile>
      <anchor>a48c000b148e60a8c3e01a028d33b6fd0</anchor>
      <arglist>(ColorValue inValue)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::clusterEntry</name>
    <filename>structstira_1_1common_1_1clusterEntry.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::ClusteringLearning</name>
    <filename>classstira_1_1common_1_1ClusteringLearning.html</filename>
    <member kind="function">
      <type></type>
      <name>ClusteringLearning</name>
      <anchorfile>classstira_1_1common_1_1ClusteringLearning.html</anchorfile>
      <anchor>acf9f22eaf1b2f68d59a59a4588e63e03</anchor>
      <arglist>(std::vector&lt; Point&lt; double &gt; &gt; inputPoints)</arglist>
    </member>
    <member kind="function">
      <type>PcaResult</type>
      <name>ComputePCA</name>
      <anchorfile>classstira_1_1common_1_1ClusteringLearning.html</anchorfile>
      <anchor>a5897871ff6242d4c07532cf42473b265</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; pointCluster &gt;</type>
      <name>ComputeKMeans</name>
      <anchorfile>classstira_1_1common_1_1ClusteringLearning.html</anchorfile>
      <anchor>a23adfc1932affe02994a075b198c98d1</anchor>
      <arglist>(std::vector&lt; Point&lt; double &gt; &gt; clusterCenters)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::imagedata::color::cmyk_t</name>
    <filename>structstira_1_1imagedata_1_1color_1_1cmyk__t.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>c</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1cmyk__t.html</anchorfile>
      <anchor>afd2059370046d6233ca5cfa60d49897a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1cmyk__t.html</anchorfile>
      <anchor>abf69753ea0298e4b21a5280da67f13ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>y</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1cmyk__t.html</anchorfile>
      <anchor>a1458e7a51457b9691b89671ec84dd785</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>k</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1cmyk__t.html</anchorfile>
      <anchor>a197a98e7167554fdc30caa416e5e3271</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::ColorBalancer</name>
    <filename>classstira_1_1image_1_1ColorBalancer.html</filename>
    <member kind="function" static="yes">
      <type>static image::Image *</type>
      <name>RunBalance</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>a9b1164d66ada8d5365f1a2503dd8edf7</anchor>
      <arglist>(image::Image *pImageIn, double weightGM=0.5)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static image::Image *</type>
      <name>RunGrayWorld</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>aa09e3101556a973a87436752d0f2fc88</anchor>
      <arglist>(image::Image *pImageIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static image::Image *</type>
      <name>RunPerfectReflector</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>a97548dedc5aade5c142e1708669d003d</anchor>
      <arglist>(image::Image *pImageIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunBalance</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>a7aae7c231157b9ae6b17bc3468944d56</anchor>
      <arglist>(Image *pImageIn, double weightGM=0.5)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunGrayWorld</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>a7c83d1ecfcec50937e6072b33b026ff2</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunPerfectReflector</name>
      <anchorfile>classstira_1_1image_1_1ColorBalancer.html</anchorfile>
      <anchor>af1dc031804692e357b1ea58edeced76f</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::ColorConstants</name>
    <filename>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</filename>
    <member kind="variable">
      <type>ColorValue</type>
      <name>mReferenceWhite</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a9e41da8a14015644d177c9ab6d4765ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>mMaxColorValue</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a666b4aa330a9d045e4937439668d7b4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sA_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a147a1bda564cfb93c068ce6af1eac01b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sB_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a3deda4cf3d8d9180dda0e0eb3da96ba4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sC_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>ad507541f0b8f70126544ed30e51df4fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sD50_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>ab8f0539a24d52330fc84adb799b607e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sD55_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a1ce4f0fdfe8e9a31ad00e44ece3cdeff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sD65_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a053b42a771e2d7c7e2f0caaf0c37f68e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sD75_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a1ff71a340ebddc37b60898e3a6e07692</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sD93_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a6199bad5681b834e4b3d578cdef59030</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sE_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a747519c360af3152848f82a6590ec6e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sF2_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>ab281d22a0aea880114c334f75673deac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sF7_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a54bef166482d4ac32217e3f4143e8175</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sF11_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a358a69bb27006336fcd96d5184e4671d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const ColorValue</type>
      <name>sPrintWhite_XYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a4259b2e9e28b6e6417d7974d15a7228e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sDifferenceThreshold</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a11b5dcd1401bc91bfd2e6935ea1c0cfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sKappa</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>aaf9e0b257a2f72f20598a316b0860d6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sEpsilon</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a74a138838906e6b9dd8f1c54538104e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sMatchingFunctionCIEx</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a478303562c697233c50712e6bacb6480</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sMatchingFunctionCIEy</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>ad8dd7006e59f0c1e98c0f1a0847666ec</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sMatchingFunctionCIEz</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a3988982daaf10752734a1b725b7deb0c</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sD50IlluminantSpectrum</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a9a338ffb7319e635ff022dcde28f6d4f</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sD65IlluminantSpectrum</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>ab4793a1b0289215d730cc06148c66834</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sAIlluminantSpectrum</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a87d9c243bcb13ea1225da9537733cc48</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sSpectralNormalizationConstantD50</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>afc4c4ca217108a35701ff6b0f22db510</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const double</type>
      <name>sSpectralNormalizationConstantD65</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a3bf8f99649fff4fa8469d93d71820588</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>sMinimumWavelength</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>aec9fcec086e6c81c6d9a8e4c7f961696</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>sMaximumWavelength</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>af6c41e7d0882a1523fea53355ae242bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>sWavelengthStepSize</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorConstants.html</anchorfile>
      <anchor>a71c97bf68136768120bc8e1e35d29997</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::ColorLookupTable</name>
    <filename>classstira_1_1filter_1_1ColorLookupTable.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::ColorValue</name>
    <filename>classstira_1_1imagedata_1_1color_1_1ColorValue.html</filename>
    <member kind="function">
      <type></type>
      <name>ColorValue</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>af9b7e189e3266a10c950de0e7d6c0831</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ColorValue</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>ad2415320b716bfe87d21d84474a13aaf</anchor>
      <arglist>(double r, double g, double b, ColorType myType=TYPE_RGB)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetColorValue</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>adebdc557e6c83adb6eda325085375f0f</anchor>
      <arglist>(double r, double g, double b, ColorType myType)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue &amp;</type>
      <name>operator=</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a9a20861de6bd6d9576f805cd5cb97c9b</anchor>
      <arglist>(const ColorValue &amp;r)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMax</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a142152e794f4d0c3017c737bf435849d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverage</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a3ab03700550bdca7e58adfff7ee4a1f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMin</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a9649e250af5c266098eacc0762e46ce8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>c</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a88bababede52b270d3ec60ea02f09a2c</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>ColorType</type>
      <name>type</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ColorValue.html</anchorfile>
      <anchor>a9702e772badc149b82968f7b0738be99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::imagedata::color::compare_neighbor_entry_t</name>
    <filename>structstira_1_1imagedata_1_1color_1_1compare__neighbor__entry__t.html</filename>
    <member kind="variable">
      <type>lut_entry_t</type>
      <name>entry</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1compare__neighbor__entry__t.html</anchorfile>
      <anchor>a7284672fd59ac165a901f14e22ad116f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dE</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1compare__neighbor__entry__t.html</anchorfile>
      <anchor>abe7a2609754a01ab22b6dd00057b300b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::CompareCurvesInImage</name>
    <filename>classstira_1_1imageanalysis_1_1CompareCurvesInImage.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::degradationestimation::CompareSmoothSharpDijk</name>
    <filename>classstira_1_1degradationestimation_1_1CompareSmoothSharpDijk.html</filename>
    <member kind="function">
      <type></type>
      <name>CompareSmoothSharpDijk</name>
      <anchorfile>classstira_1_1degradationestimation_1_1CompareSmoothSharpDijk.html</anchorfile>
      <anchor>a85dd578d49321702c75d289ec23d1b5b</anchor>
      <arglist>(Image *pImage1, Image *pImage2, std::string name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CompareSmoothSharpDijk</name>
      <anchorfile>classstira_1_1degradationestimation_1_1CompareSmoothSharpDijk.html</anchorfile>
      <anchor>aeb907b51818f72735562582bd7b04afa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1degradationestimation_1_1CompareSmoothSharpDijk.html</anchorfile>
      <anchor>a68cb9153a6cc87f11fd35eed446c6fbc</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::ComputeOrientation</name>
    <filename>classstira_1_1steerable_1_1ComputeOrientation.html</filename>
    <member kind="function">
      <type></type>
      <name>ComputeOrientation</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>a794aa9a24d5b71dbe60af86c7d2406a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ComputeOrientation</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>aae82d5d1a7eddd9d651f84d98e90eb4f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>ConvertAngleToHSVMap</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>a465119421cfcbda982bfb2f15cd7ea64</anchor>
      <arglist>(double angle)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>ConvertAngleToRGBMap</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>a9130d6ccec112eddcbbdeb816fb9f6d7</anchor>
      <arglist>(double angle)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OrientationGrid *</type>
      <name>ComputeDominantOrientationInputFreemanAdelson</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>a332320c48ac7dc5847db91ed83946751</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pResponseH2a, ArrayGrid&lt; double &gt; *pResponseH2b, ArrayGrid&lt; double &gt; *pResponseH2c, ArrayGrid&lt; double &gt; *pResponseH2d, ArrayGrid&lt; double &gt; *pResponseG2a, ArrayGrid&lt; double &gt; *pResponseG2b, ArrayGrid&lt; double &gt; *pResponseG2c)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OrientationGrid *</type>
      <name>ComputeDominantOrientationInputComplexPyramidLevel</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeOrientation.html</anchorfile>
      <anchor>a1932f153484bcb0efaa8cca261848cd6</anchor>
      <arglist>(PyramidLevel&lt; std::complex&lt; double &gt; &gt; *pPyrLevel)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::ComputeSteerableFilteredImages</name>
    <filename>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</filename>
    <member kind="function">
      <type></type>
      <name>ComputeSteerableFilteredImages</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>ac2d1a8d67fc576ffdb16e4c9afc0b53d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *mpSourceGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ComputeSteerableFilteredImages</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a81c0e7ede8ddbf3a4033c753d7d77e4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Run</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a90c5248d1e1499153a16b1ee5335eb60</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>OrientationGrid *</type>
      <name>GetOrientationGrid</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a9c03789648c3d3e9ba5dff69fd16ce7a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>InterpolateG</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a24631c710cbf818fdb86a74a923e0f59</anchor>
      <arglist>(double theta)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>InterpolateH</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a78c73ea040de145ee151ff43fb6b27ab</anchor>
      <arglist>(double theta)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>FilterAlongDominantOrientationG</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>adcb0865bdff30d432aad4f6aa6dc0354</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>FilterAlongDominantOrientationH</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a27509fc99989c661b78515af931f0117</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetH2a</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>afdf9ba7e4e0e96fc7102f2e0a43f7df2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetH2b</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a46182b3deaaf0b21c0620e6bde8ae4d1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetH2c</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a4c959d3d544b4e04953f356889f53877</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetH2d</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>acb465bb964a31d254441590e6089922a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetG2a</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>ab5146127d39597be4a7ab999a2769a7a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetG2b</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a8526bb182d1d5b4d250cdb085c4a8e25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetG2c</name>
      <anchorfile>classstira_1_1steerable_1_1ComputeSteerableFilteredImages.html</anchorfile>
      <anchor>a950cfc8631b5ba81c857928135dbc44b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::ContourTracing</name>
    <filename>classstira_1_1imageanalysis_1_1ContourTracing.html</filename>
    <member kind="function">
      <type></type>
      <name>ContourTracing</name>
      <anchorfile>classstira_1_1imageanalysis_1_1ContourTracing.html</anchorfile>
      <anchor>a31768153bcf8d5aae1f120cd56591753</anchor>
      <arglist>(double alphaStraight, double alphaNotStraight, std::string filePath)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ContourTracing</name>
      <anchorfile>classstira_1_1imageanalysis_1_1ContourTracing.html</anchorfile>
      <anchor>a75a7ad41260dc52e8ee1233bd7174116</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; ArrayGrid&lt; double &gt; *, ArrayGrid&lt; double &gt; * &gt;</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1ContourTracing.html</anchorfile>
      <anchor>a5e28484b0ceaa4cf20268d48f34ac780</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int ID=0)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>RunLeftRight</name>
      <anchorfile>classstira_1_1imageanalysis_1_1ContourTracing.html</anchorfile>
      <anchor>af3a7aa5ca2bdb620f1e0e37ca50ece3d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int ID)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>RunRightLeft</name>
      <anchorfile>classstira_1_1imageanalysis_1_1ContourTracing.html</anchorfile>
      <anchor>ab7f738b99f85293f05727e7cdd5a552d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int ID)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::CriticallySubsampledTransform</name>
    <filename>classstira_1_1wavelet_1_1CriticallySubsampledTransform.html</filename>
    <base>stira::wavelet::Wavelet</base>
    <member kind="function">
      <type></type>
      <name>CriticallySubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1CriticallySubsampledTransform.html</anchorfile>
      <anchor>a6d835cb8140469ab098a7b228426e22e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~CriticallySubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1CriticallySubsampledTransform.html</anchorfile>
      <anchor>a99ecbc5054d53b0ffbcbc726f08b0eb6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1wavelet_1_1CriticallySubsampledTransform.html</anchorfile>
      <anchor>a91a471358697f4456c0430a78e70bf21</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceGrid, int nrScales)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1wavelet_1_1CriticallySubsampledTransform.html</anchorfile>
      <anchor>af16e051b3b454b100976aa990fb779ff</anchor>
      <arglist>(double threshold=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::Curve</name>
    <filename>classstira_1_1common_1_1Curve.html</filename>
    <member kind="function">
      <type></type>
      <name>Curve</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a750c27733dbc2b38ce47b0744469b925</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Curve</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a622cb06079b2c600b65467a7f4523b2b</anchor>
      <arglist>(std::vector&lt; Point&lt; int &gt; &gt; pointsOnCurve)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverageX</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a97dd849dc1e6864083c7c816684a06e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverageY</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>aed87e91effbf486b309d17a5f6bfa4bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCorrespondingY</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a86144021922a03354e6d9c24e2a5555d</anchor>
      <arglist>(int x) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetLength</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a77400ae12c35add16be5055f177dc5f1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetY</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>ae7a83996875f2eb77ef919c1beef8cb7</anchor>
      <arglist>(int x) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddPoint</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>aaa9abc7537eab53a4ef7e21307bc9dfb</anchor>
      <arglist>(Point&lt; int &gt; point)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddPoints</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a42abe3f5e8f2d2ff6b3eda4ae16668de</anchor>
      <arglist>(std::vector&lt; Point&lt; int &gt; &gt; points)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>GetPoints</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a521cfb875604f3b4b9f2b7e5275fbf41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetStartPoint</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a0751a65230d3ed2f89af50b3d831751f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetEndPoint</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a3962cc5ba05189fb20e2aa54f98c4a1d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>GetExtremePointsX</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a22c4e921ef5abd172c66f52b77270cf2</anchor>
      <arglist>(int &amp;xMin, int &amp;xMax, bool usePoints=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>GetPointsMinimumX</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a2666a93a05a3ec837756a669efe9754d</anchor>
      <arglist>(int &amp;xMin, bool usePoints=false)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>GetPointsMaximumX</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a39f94ef9995a3d4c20fbd5fb66aa5d37</anchor>
      <arglist>(int &amp;xMax, bool usePoints=false)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetPoint</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>aa95afbe0f5a9bf7b895616f77b05c660</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SortOnCoordinateX</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>afd03e0f16e19ca01da0fd71eee97a54c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SortOnCoordinateY</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a81b0fa6b82efb8ac87cf01cdd5eaf97e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WritePointsToStdOut</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a04486ac08c35e90ca38e4097a682299c</anchor>
      <arglist>(int intervalSize=10)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetIsUsed</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a0165a955df6f30a231e378b1fca778d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetIsUsed</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>aef20574c0c5d6135c85cbb0a1aa8a074</anchor>
      <arglist>(bool isUsed)</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; Point&lt; int &gt;, Point&lt; int &gt; &gt;</type>
      <name>GetClosestEndPoints</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>ae6858028181128324eb4dc7d6b1fb059</anchor>
      <arglist>(Curve otherCurve)</arglist>
    </member>
    <member kind="function">
      <type>Curve</type>
      <name>CreateMergedCurve</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a22d4a6976044b394b1848f2b28354d42</anchor>
      <arglist>(Curve otherCurve)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ConnectToCurve</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a0472aa5bb29ef524b362a2d72c407fb1</anchor>
      <arglist>(Curve otherCurve)</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; double, double &gt;</type>
      <name>ComputeVerticalDistanceToCurve</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a8088e1426bd3a7d6f6ad96ed7509083f</anchor>
      <arglist>(Curve otherCurve)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AreNeighbors</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>af3a1c6c82512ac26526b9f35a51a8a1b</anchor>
      <arglist>(Point&lt; int &gt; inPoint1, Point&lt; int &gt; inPoint2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SmoothCurveY</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a2f212859e1ddf8e726e346c04a5f9b23</anchor>
      <arglist>(int smoothHalfDistance)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>WritePointsToText</name>
      <anchorfile>classstira_1_1common_1_1Curve.html</anchorfile>
      <anchor>a9b6c4ba6fc319e67b99c83941ac05355</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::histogram::CurveSegment</name>
    <filename>structstira_1_1histogram_1_1CurveSegment.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::CurveSet</name>
    <filename>classstira_1_1common_1_1CurveSet.html</filename>
    <member kind="function">
      <type></type>
      <name>CurveSet</name>
      <anchorfile>classstira_1_1common_1_1CurveSet.html</anchorfile>
      <anchor>a4e35b31105ca0691bdb6650d2d4d57bf</anchor>
      <arglist>(std::vector&lt; Curve &gt; curveSet, int ID)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Curve &gt;</type>
      <name>GetCurveVector</name>
      <anchorfile>classstira_1_1common_1_1CurveSet.html</anchorfile>
      <anchor>a5251bc7f810480543ceda568f916dd5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfCurves</name>
      <anchorfile>classstira_1_1common_1_1CurveSet.html</anchorfile>
      <anchor>a759ba5299ad03af310896da473cf9958</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetCurveSetID</name>
      <anchorfile>classstira_1_1common_1_1CurveSet.html</anchorfile>
      <anchor>abf4ad231c2eecc2d891d2f66ca51e16b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Curve</type>
      <name>GetTopCurve</name>
      <anchorfile>classstira_1_1common_1_1CurveSet.html</anchorfile>
      <anchor>a2a91f134b7fdba8813a739751cfca91d</anchor>
      <arglist>(int minimumLength=400)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::CWTPyramid</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</filename>
    <base>Pyramid&lt; std::complex&lt; double &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>CWTPyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>ac6e2919a093a2ebe3780068e399ec5be</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceBand, int myNrScales)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CWTPyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>ac21306f5b26dc4f7de6fdc5935b88a59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetLowPassResidual1</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>a38f870f2cb44566b336aedd3b4f806f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowPassResidual1</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>a6a286ec7b7ef4061741431dbc7e327c7</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetLowPassResidual2</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>a68009866b3837dc2ba762aa55f98d433</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowPassResidual2</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1CWTPyramid.html</anchorfile>
      <anchor>a89962dc9b128d645333c4a265ba997d6</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBand)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::dataRow</name>
    <filename>structstira_1_1common_1_1dataRow.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>x</name>
      <anchorfile>structstira_1_1common_1_1dataRow.html</anchorfile>
      <anchor>ae61f121a5c990466ee37a3c13fe3f5ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>y</name>
      <anchorfile>structstira_1_1common_1_1dataRow.html</anchorfile>
      <anchor>ac0e7baa6604b92fd0021b03ac64df75b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>delta</name>
      <anchorfile>structstira_1_1common_1_1dataRow.html</anchorfile>
      <anchor>ad08e14625d57a29b83938617d4eb609d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>m</name>
      <anchorfile>structstira_1_1common_1_1dataRow.html</anchorfile>
      <anchor>aef4c24111a57218f928dbe8f679fe6e9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::DeconvolveMaster</name>
    <filename>classstira_1_1deconvolve_1_1DeconvolveMaster.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>afa54334f994ea17b96fd6aa26445f6e0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetDegradedImage</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>a405308467a3a1ad59353aa7f21c00897</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDegradedImage</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>a08c166ee3e969ba27abc47e6697ef7d5</anchor>
      <arglist>(Image *pDegradedImage)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetPSF</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>ae7640b8eed5d3e4cfa9c6d5d7d472306</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPSF</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>aec6bcc1e26db3b83f8fd819548ba3557</anchor>
      <arglist>(Image *pPSF)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetRestoredImage</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>a8d679c85d8e8abb963456b874c0ae8ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigmaNoise</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>a0acdfcd0a31b6c67fb50cda1ac5794d7</anchor>
      <arglist>(double sigma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigmaNoise</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>ae1b7381bb06a67448f33eaa61ce5ee69</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>IsReadyToRun</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>af585d8a812c717c357adafc9539ada72</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>DeconvolveMaster</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>ae9dd02f846e494c9a983c62924d5ba60</anchor>
      <arglist>(Image *pDegradedImage)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>DeconvolveMaster</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>ade80bad643f5b6e1ab25bdddeef0b928</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~DeconvolveMaster</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>aba058adbdf529f8f0017e6c2b7c10e4e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>AreParentConditionsOK</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>a73e30b7d9eb3b3efbfbca83e3c4b3b70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image *</type>
      <name>mpDegradedImage</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>aca2d5d7a5177435516e015ce9d810d2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image *</type>
      <name>mpRestoredImage</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>af1d710fd0a129f5af987db0de266bf3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image *</type>
      <name>mpPSF</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>ac024edcd4c6bd370c8a48f53c1f240fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mSigmaNoise</name>
      <anchorfile>classstira_1_1deconvolve_1_1DeconvolveMaster.html</anchorfile>
      <anchor>af458b824cfcc3b0aa8abf3c699dafde9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::DifferenceOfGaussians</name>
    <filename>classstira_1_1filter_1_1DifferenceOfGaussians.html</filename>
    <member kind="function">
      <type></type>
      <name>DifferenceOfGaussians</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>a9396fbe48d29bbc7b3c6129487b58a81</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DifferenceOfGaussians</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>a813d47f4a659bc0a47d8707f84fa04e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>a6ced3dc01d43897f7f3bfdcb87b0ae83</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>a78a79817e1e7714cea6c1f74b163eba6</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigmaX1, double sigmaX2, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>a47194cc9525ed4bdf808cc453a720249</anchor>
      <arglist>(Image *pImageIn, double sigmaX1, double sigmaY1, double sigmaX2, double sigmaY2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1DifferenceOfGaussians.html</anchorfile>
      <anchor>ab1a31875d556546b3dac8b339a253bc7</anchor>
      <arglist>(Image *pImageIn, double sigmaX1, double sigmaX2, double sigmaY)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::DistanceTransform</name>
    <filename>classstira_1_1imageanalysis_1_1DistanceTransform.html</filename>
    <member kind="function">
      <type></type>
      <name>DistanceTransform</name>
      <anchorfile>classstira_1_1imageanalysis_1_1DistanceTransform.html</anchorfile>
      <anchor>a2695145eafd11265aaee31748c03924c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DistanceTransform</name>
      <anchorfile>classstira_1_1imageanalysis_1_1DistanceTransform.html</anchorfile>
      <anchor>a02de9978ee0c1566ccc9165df3afcaf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1DistanceTransform.html</anchorfile>
      <anchor>aa0ef484dfac900978490a884f16c7192</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::DistinctColorGenerator</name>
    <filename>classstira_1_1imagedata_1_1color_1_1DistinctColorGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>DistinctColorGenerator</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1DistinctColorGenerator.html</anchorfile>
      <anchor>ab64d547a0c25fd9c8677b4b195178609</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DistinctColorGenerator</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1DistinctColorGenerator.html</anchorfile>
      <anchor>a543408cfe623298eab94b248175b32ac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>GenerateNewColor</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1DistinctColorGenerator.html</anchorfile>
      <anchor>a19dfff00976b62570af1200d4209ae23</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::DrawFigures</name>
    <filename>classstira_1_1common_1_1DrawFigures.html</filename>
    <member kind="function">
      <type></type>
      <name>DrawFigures</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a0d08ee6c232d725e0e835df59efde710</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DrawFigures</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>abef73bf58c8423d2abc0ca631701a10d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>BresenhamDrawLine</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a839b2f2459fdb189251c6def4e69d706</anchor>
      <arglist>(int startX, int startY, int endX, int endY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>BresenhamDrawLine</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a81ecbabf95aafd9fca05317d4688095e</anchor>
      <arglist>(Point&lt; int &gt; startPoint, Point&lt; int &gt; endPoint)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a704a2b20e5262997a8782f7f96477ab1</anchor>
      <arglist>(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsInsideEllipse</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a199efea43c2e6f6971e171065686fd85</anchor>
      <arglist>(double xTest, double yTest, double xCenter, double yCenter, double majorAxis, double minorAxis, double angleRadians)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a9c49f62c5338db3a70a09a8a41a20471</anchor>
      <arglist>(Point&lt; int &gt; topLeftCorner, Point&lt; int &gt; bottomRightCorner)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>ad9da927de110e513d0972c028f2e17b1</anchor>
      <arglist>(RectangularROI&lt; int &gt; rroi)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; int &gt; &gt;</type>
      <name>DrawCircle</name>
      <anchorfile>classstira_1_1common_1_1DrawFigures.html</anchorfile>
      <anchor>a5ab5559b385558c3ebb700e4d1321e75</anchor>
      <arglist>(Point&lt; int &gt; center, int radius)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::DrawImageTools</name>
    <filename>classstira_1_1image_1_1DrawImageTools.html</filename>
    <member kind="function">
      <type></type>
      <name>DrawImageTools</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a4f0f87c2e36a015d3e6faf463259bbb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~DrawImageTools</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>aea44e124f55e54e2b13a7da7c3416a96</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawSquare</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a6830d4e348ef457c7c720856bbb6a7b1</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myCenterPoint, int halfLength, ColorValue newColor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>af3240b21089480e8d1b0112adb3d0cda</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::Point&lt; int &gt; myTopLeftPoint, common::Point&lt; int &gt; myBottomRightPoint, double newValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a6740ea39344c34f0fe9103c7d89ecbfe</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::RectangularROI&lt; int &gt; rroi, double newValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a9688927b11dfe20ade1272a9673697c3</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myTopLeftPoint, common::Point&lt; int &gt; myBottomRightPoint, double newValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>abdf3e0977c3784d835aa48dd8d34590f</anchor>
      <arglist>(Image *pImageInOut, common::RectangularROI&lt; int &gt; rroi, double newValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a5616c2764b5eea47799569ee2838bf39</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myTopLeftPoint, common::Point&lt; int &gt; myBottomRightPoint, ColorValue newColorValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawRectangle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a7711b40ab9b7d13ffc10aa7ebbdae824</anchor>
      <arglist>(Image *pImageInOut, common::RectangularROI&lt; int &gt; rroi, ColorValue newColorValue, bool fillSurface)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawDisk</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>af7b02566d729a96c4b847a8d2bce29b6</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myCenterPoint, double radius, ColorValue newColor=ColorValue(255, 0, 0, TYPE_RGB))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawDisk</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a2189b82b3bb99580d99c432cfd7c6a69</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::Point&lt; int &gt; myCenterPoint, double radius, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Plot8CirclePoints</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a390a06e0da8059c40280b1d35862b913</anchor>
      <arglist>(Image *pImage, int xCenter, int yCenter, int x, int y, ColorValue cv)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawCircle</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>ac80d38a7eb27fcaa1f51991776c18a96</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myCenterPoint, double radius, ColorValue newColor=ColorValue(255, 0, 0, TYPE_RGB))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPolygon</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>af632df7c2c0b5bbe90ceb52b09fe1770</anchor>
      <arglist>(Image *pImageInOut, common::Polygon myPolygon, ColorValue newColor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPolygon</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a13dd17d02622e6cba561f8bcc2d506d1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::Polygon myPolygon, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::Point&lt; int &gt; &gt;</type>
      <name>DrawLine</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a9ef04b5d207938fde72875503dff96ab</anchor>
      <arglist>(Image *pImageInOut, int xStart, int xStop, int yStart, int yStop, ColorValue newColor=ColorValue(255, 0, 0, TYPE_RGB))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::Point&lt; int &gt; &gt;</type>
      <name>DrawLine</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a7bd3c04e97a2151d141ce60fd17e4c58</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; startPoint, common::Point&lt; int &gt; stopPoint, ColorValue newColor=ColorValue(255, 0, 0, TYPE_RGB))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::Point&lt; int &gt; &gt;</type>
      <name>DrawLine</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>adfda9f120bee64b09339bdca4b699992</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::Point&lt; int &gt; startPoint, common::Point&lt; int &gt; stopPoint, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoint</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a31c50aee6d0d783febaedba045fa5aef</anchor>
      <arglist>(Image *pImageInOut, int x, int y, ColorValue newColor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoint</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>aa8b23e319624bb9972b7bda0972b7670</anchor>
      <arglist>(Image *pImageInOut, common::Point&lt; int &gt; myPoint, ColorValue newColor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoint</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a54c5cdb8449f0f065d84382e0f4822eb</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, common::Point&lt; int &gt; myPoint, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoint</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a0f0b247f1414bbacb7d2cde4b98ea57f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, int x, int y, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoints</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>aab0667d4824dceb150603e9e56885701</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridInOut, std::vector&lt; common::Point&lt; int &gt; &gt; vPoints, double newValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>DrawPoints</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a22e8a78c5f328cb9268428a2ebce99e9</anchor>
      <arglist>(Image *pImageInOut, std::vector&lt; common::Point&lt; int &gt; &gt; vPoints, ColorValue newColor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>DrawBoolOnInput</name>
      <anchorfile>classstira_1_1image_1_1DrawImageTools.html</anchorfile>
      <anchor>a554fd6043897b67a6e188026ffec7c53</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, ArrayGrid&lt; bool &gt; *pGridBool, ColorValue cv=ColorValue(255, 0, 0, TYPE_RGB))</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Random::dSquared</name>
    <filename>structRandom_1_1dSquared.html</filename>
  </compound>
  <compound kind="class">
    <name>Example</name>
    <filename>classExample.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::ExecutionTimer</name>
    <filename>classstira_1_1common_1_1ExecutionTimer.html</filename>
    <member kind="function">
      <type></type>
      <name>ExecutionTimer</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a89d3657e6c1b7a3ba303b75c9fb9db92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ExecutionTimer</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>ab87506dae25bf08d68feaa5dfb47dc75</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetCurrentTime</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a30987b67594e2e450a50d293f9bfab1e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>StartTimer</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>abd788e726399058d11856bac7665da24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>StopTimer</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a9e585053ddb769b889ee28446024afd7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetElapsedUserTimeInSeconds</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a0aa4f132446730b4ac03da698c75b6c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetElapsedSystemTimeInSeconds</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a71e6ddcd5bdfabc5e783aaf4ed1a19af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>GetElapsedRealTimeInSeconds</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a57ce7fec1864b910d3970e8d75e81628</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTimeAsUserAndSystemTimes</name>
      <anchorfile>classstira_1_1common_1_1ExecutionTimer.html</anchorfile>
      <anchor>a74feb8acad7976d56a487d087302cf9a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::FFT</name>
    <filename>classstira_1_1fouriertools_1_1FFT.html</filename>
    <member kind="function">
      <type></type>
      <name>FFT</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>ae787d3775bfb861a5702686499bff52c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FFT</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a6debc10b4432446506ebbe1f8e89db45</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>CreateComplexGridFromRealGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a6cfc1dfeab5da5630f257f8ff9701135</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>CreateRealGridFromComplexGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a1d724a2df172572936b55c8d00baf0c1</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputePowerSpectrum</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>afb62fc7eeca49450dbaa2848d783c7f6</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputeLogPowerSpectrum</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a2fc538d9937faf426276437513ab50d7</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; double &gt;</type>
      <name>ComputeRadiallyAveragedSpectrum</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a71d730fc389ac07c51ca8c1f8fb8e49d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputImage, int thetaSteps=500)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Convolve</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>ab5f019245ef69301ccd5ae045d7368b6</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, ArrayGrid&lt; double &gt; *pFilterKernel)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Convolve</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>ab2df056f510bdc6558a983e0b92d040a</anchor>
      <arglist>(Image *pInputImage, ArrayGrid&lt; double &gt; *pFilterKernel)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>GaussConvolve</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a56b910fb0e4c0ff0a406675b9d50da14</anchor>
      <arglist>(Image *pInputImage, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GaussConvolve</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>adb1d7fb300f69e38b72b1eabe82debc3</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>ApplyTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a81ab0a4eecc3d7c484c4584b1c561701</anchor>
      <arglist>(FFTBand *pFFTImageData, ArrayGrid&lt; double &gt; *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>ApplyTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>abd9962633646ff66debb229af8d728f7</anchor>
      <arglist>(FFTBand *pFFTImageData, FFTBand *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>ApplyTransferFunctionFFT</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>acfec36aa2830824472c93a1c1b408ef1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, ArrayGrid&lt; double &gt; *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>ApplyTransferFunctionFFT</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a0f0b12aa687e0207bd0c73c9b4a63b1d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, FFTBand *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>ApplyTransferFunctionFFT</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a386d27353013827a2fd2ef6635a4b9ff</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pInputGrid, FFTBand *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ApplyTransferFunctionSpatial</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a5a41e21628c2b0f853dbc8b424ca3f76</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, ArrayGrid&lt; double &gt; *transferFunction, FFTDataType myDataType=RE)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::pair&lt; ArrayGrid&lt; double &gt; *, ArrayGrid&lt; double &gt; * &gt;</type>
      <name>ApplyTransferFunctionSpatialComplex</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a15c2ef76e5b20e997f83f88d75328ea2</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid, ArrayGrid&lt; double &gt; *transferFunction)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>SuppressOuterFrequencies</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a2b40a38b65a551806cd65026464f06ab</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputGrid)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>RescaleGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>aed37359d82034f1df98e9127abd464e4</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double newMin, double newMax)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>WriteFFTDataToPPM</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFT.html</anchorfile>
      <anchor>a4f77601e59df09ab3f1ac10fa54728e1</anchor>
      <arglist>(FFTBand *pFFTData, FFTDataType myDataType, char *pFileName, double factor)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::FFTBand</name>
    <filename>classstira_1_1fouriertools_1_1FFTBand.html</filename>
    <member kind="function">
      <type></type>
      <name>FFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a735733fa895e39f6832371fc6443e1f2</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, bool isreal=true)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a0f048d49b91146806d2aa9cc440258ff</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a692aef79634cf853dccd5149e7e249a9</anchor>
      <arglist>(int width, int height, std::complex&lt; double &gt; initValue=std::complex&lt; double &gt;(0.0, 0.0))</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a4f32f8c6b9e5444d08e53cce2cc9273a</anchor>
      <arglist>(FFTBand &amp;otherFFTBand)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a2c4aa9cb86c0bbbe7df04cc84c631d8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>FFTBand *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>acba86c1ce6b5b06847325b4e5da39aa9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>GetValue</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a1f2093270702487911313545f5396c60</anchor>
      <arglist>(int x, int y) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>afa6b7e1024f4e25ab5333f45846e9879</anchor>
      <arglist>(int x, int y, std::complex&lt; double &gt; complexValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetValue</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>aba6b41096caed089dda2f48f6a1dd0f8</anchor>
      <arglist>(int x, int y, double realValue, double imagValue)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>ad80e4f5d532857068f7bc114ede3738d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a00728cedfc2850b9dbdd31c6126a2c98</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyForwardTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a09c35bdddba8ef4c9fe67bf08cd8b542</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyInverseTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a0ef1cc48892b571d62a165950d2c0bc0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PointMirrorBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a36be60a77d698304e5b87504a1c18466</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ConvertToRealGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>ab01a0bac58ed2a9ce8ffcdf19ce36aab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ConvertToImaginaryGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a56d2bcccd28a7aff39e1c85f006e5143</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>ConvertToComplexGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a4fc79d5c7e79a92d0961cc6d9c0d4b54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ExportAbsImage</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a8277b157259a57eaa471d2a1bef6d262</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a18d711e61eb7d4ccfbdbef837c0f8703</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Conjugate</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a95c78ff5ba955a259a11badc3d62652c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBandMaximum</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>adb75d103cef2a7f6b842df1a6f0e0c54</anchor>
      <arglist>(FFTDataType type)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBandMinimum</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>aac1890bb8dfc2c187d84b41de42b673d</anchor>
      <arglist>(FFTDataType type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Multiply</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a8844b1748645805ec6be565b26888d76</anchor>
      <arglist>(FFTBand *other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Multiply</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a728e2cfd85d9bb905ae08072add25b84</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *grid)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Multiply</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>ab75293374dab5f08a149e1dfffbe3907</anchor>
      <arglist>(std::complex&lt; double &gt; myFactor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Multiply</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTBand.html</anchorfile>
      <anchor>a85711ddba5286d35bf4cbf4cf8fb5a88</anchor>
      <arglist>(double myFactor)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::FFTCalculator</name>
    <filename>classstira_1_1fouriertools_1_1FFTCalculator.html</filename>
    <member kind="function">
      <type></type>
      <name>FFTCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a6ec6f077099e6d05e5de25442c04df32</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pComplexGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FFTCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a57f2b8d0de0199325c6d8a83cf56a87f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FFTCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a2bd47cb4f05d45c00b712d3b3f7675dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>ApplyForwardTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a99789a2d05e095b72237129e8e44fbfe</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>ApplyInverseTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a47246a485a7e9ab3bdc247d59da26862</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a8b8584235eb5a83f0e085fd0bcc853a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SwitchQuadrants</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>abcd64c4144100da835d91df13586d260</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>CreateLibData</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>abee7dbc3f97de6fc66576fc24d3b227a</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridin)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>CleanLibData</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a3914ca2dbb6713d4a889f014ed9ff17a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>WriteResultInFFTBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>afdbaeb589bcd01a8b09a61094b20ce0a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>mpComplexGrid</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a6f3437d2442e8deb48fd2d2fffac36d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>ae453101bc6c7f3d7ff7b4f2885fe7d2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTCalculator.html</anchorfile>
      <anchor>a82b2ad4d7070a971b7c74e223f6705dd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::FFTWCalculator</name>
    <filename>classstira_1_1fouriertools_1_1FFTWCalculator.html</filename>
    <base>stira::fouriertools::FFTCalculator</base>
    <member kind="function">
      <type></type>
      <name>FFTWCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTWCalculator.html</anchorfile>
      <anchor>a6d5fcc0f9547365b2bae560e754373c7</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pComplexGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FFTWCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTWCalculator.html</anchorfile>
      <anchor>ae33cba254c0ab8cbc12a7915a6a0aa10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FFTWCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTWCalculator.html</anchorfile>
      <anchor>a707ef17491ebf19bcdb8ce7f34736697</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ApplyForwardTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTWCalculator.html</anchorfile>
      <anchor>a674d533adee538f9fabb8f4299b10eb8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ApplyInverseTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1FFTWCalculator.html</anchorfile>
      <anchor>a34f007c871acc3a6b01c343c9805f73a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::FileAccess</name>
    <filename>classstira_1_1common_1_1FileAccess.html</filename>
    <member kind="function">
      <type></type>
      <name>FileAccess</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a796329286dd8e5ae92c377b72b57f2b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FileAccess</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>ab30b4e0e3ed759dca06dc943a5066760</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; std::string &gt;</type>
      <name>ListFilesInSubFoldersInFolder</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a8bb6105479db58670c36807bc0b0d722</anchor>
      <arglist>(std::string pathToAccess, std::string prefix, std::string extension, bool separatorIsUnderscore=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; std::string &gt;</type>
      <name>ListFilesOfType</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a1204365fe9d5538a44f02fc052b1b17f</anchor>
      <arglist>(std::string pathToAccess, std::string prefix, std::string extension, bool usePrefix, bool separatorIsUnderscore=false, int startNrImage=-1, int maxNrFiles=-1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>FindFileName</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>af38ba322651ff9ff7b66838d637ab3e6</anchor>
      <arglist>(std::vector&lt; std::string &gt; fileList, int frameNr)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>CheckIfDirectoryExists</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a866f0fc9fedb200b72aee787c8f17b89</anchor>
      <arglist>(const std::string dirName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>CreateNewDirectory</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a2f9bd267e7ef56af4d1f28aaf00a1484</anchor>
      <arglist>(std::string dirName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>CreateSymbolicLink2File</name>
      <anchorfile>classstira_1_1common_1_1FileAccess.html</anchorfile>
      <anchor>a5c0f17f25cb765049fc6d84e2faa57ab</anchor>
      <arglist>(std::string sourcePathAndFileName, std::string linkPathAndFileName)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::FindMaximalIncludedRectangles</name>
    <filename>classstira_1_1imageanalysis_1_1FindMaximalIncludedRectangles.html</filename>
    <member kind="function">
      <type></type>
      <name>FindMaximalIncludedRectangles</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FindMaximalIncludedRectangles.html</anchorfile>
      <anchor>a15ddab4914e2f7d18813bd507e5ad777</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::RectangularROI&lt; int &gt; &gt;</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FindMaximalIncludedRectangles.html</anchorfile>
      <anchor>ab84be1404b1318bdb72b6f82687cef00</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pObjectGrid)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::FisheyeCorrector</name>
    <filename>classstira_1_1image_1_1FisheyeCorrector.html</filename>
    <member kind="function">
      <type></type>
      <name>FisheyeCorrector</name>
      <anchorfile>classstira_1_1image_1_1FisheyeCorrector.html</anchorfile>
      <anchor>a5abff9df8f5716a90f7988ba4c2c81c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FisheyeCorrector</name>
      <anchorfile>classstira_1_1image_1_1FisheyeCorrector.html</anchorfile>
      <anchor>a80ce323af9fe55b8c24db95561f52746</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>ApplyCorrect</name>
      <anchorfile>classstira_1_1image_1_1FisheyeCorrector.html</anchorfile>
      <anchor>a51dfa0bc5813675395b47dfe0279b14c</anchor>
      <arglist>(Image *pImageIn, double strength, double zoom)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyCorrect</name>
      <anchorfile>classstira_1_1image_1_1FisheyeCorrector.html</anchorfile>
      <anchor>aa9728c82e695d6ee4ace8dc9f3f77f98</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, ArrayGrid&lt; double &gt; *pGridOut, double strength, double zoom)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::FitCurve</name>
    <filename>classstira_1_1common_1_1FitCurve.html</filename>
    <member kind="function">
      <type></type>
      <name>FitCurve</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a8033109cd128e3c52603a21f38b21bdb</anchor>
      <arglist>(std::vector&lt; Point&lt; int &gt; &gt; inputPoints)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FitCurve</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a66cd85f9c1bc0864c0681539ee77a9b6</anchor>
      <arglist>(std::vector&lt; Point&lt; double &gt; &gt; inputPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPoints</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a68fa712edc64e9ae2117d73ab045ee00</anchor>
      <arglist>(std::vector&lt; Point&lt; double &gt; &gt; inputPoints)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPoints</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a4a300479b9fb2311ec38a4db6ce4d317</anchor>
      <arglist>(std::vector&lt; Point&lt; int &gt; &gt; inputPoints)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>FitLinear</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>af89c29eef80abb6f6f733079cc71b863</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>FitQuadratic</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a2fbc7985075125377a69afe57e54030f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>FitExponential</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a17c7447b5af2017d0bff965a90e93309</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>GetAllAbsoluteErrors</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>adc976052306b25c26e73dda790cd403e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMeanAbsoluteError</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>abe285ac6460737e7c21e48885ea33bbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>PolynomialFit</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a5b91c437c3e78d373afee839d7e802a4</anchor>
      <arglist>(int polynomialDegree)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>GaussianFitLeastSquares</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a16b11e9a28c2f0e9ab60e922ba48989e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>WriteToDisk</name>
      <anchorfile>classstira_1_1common_1_1FitCurve.html</anchorfile>
      <anchor>a896bc8f267bb140c2c9ce321867e32d6</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fitRec</name>
    <filename>structfitRec.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::FixedBuffer</name>
    <filename>classstira_1_1common_1_1FixedBuffer.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>FixedBuffer</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>ac18ca79555b42f1553711314a7b7ca2c</anchor>
      <arglist>(int maxSize, SideOverflow mySide=DELETE_FROM_BEGIN)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FixedBuffer</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>adac974b0f0da85e4df224ed2ff64b551</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddElement</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>a3a9b765a5ba226108fc5e40de501b88b</anchor>
      <arglist>(T newElement)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InsertElementFromStart</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>a04836a7fbc8edc8d9de1e3625d7f12cd</anchor>
      <arglist>(T newElement, int positionFromStart=0)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetElementFromStart</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>a61b763ed4c253c6ac68ae5ca7f73a865</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetElementFromEnd</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>abcc4cc04079458f25eeffc8e7ed0774e</anchor>
      <arglist>(int index)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSize</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>a27300337e61c13256ae0ac4a5db381d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Clear</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>ad939e53659345e3ebcc7edcb1c9cf20a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>mMaxSize</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>a1bedc98f902e23478918329b7f7d9a2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>SideOverflow</type>
      <name>mSide</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>ac419264ca2c55301534d9cfe92eed21c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; T &gt;</type>
      <name>mvVector</name>
      <anchorfile>classstira_1_1common_1_1FixedBuffer.html</anchorfile>
      <anchor>ae2d463bc2564b9c1035388e173d0e2a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::FlashROF</name>
    <filename>classstira_1_1FlashROF.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::histogram::FloatHistogram</name>
    <filename>classstira_1_1histogram_1_1FloatHistogram.html</filename>
    <base>HistogramMaster&lt; double &gt;</base>
    <member kind="function">
      <type></type>
      <name>FloatHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a2103a41815135acab3c7bb0a3bfa03ee</anchor>
      <arglist>(int nrOfBins, int nrBands)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FloatHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>ae009d8824183d2a043ce8b2ce446cea9</anchor>
      <arglist>(IntHistogram *pIntHistogram, bool requiresNormalization)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FloatHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a54775641000788747571b8037650a303</anchor>
      <arglist>(const FloatHistogram &amp;pFloatHistogram)</arglist>
    </member>
    <member kind="function">
      <type>FloatHistogram *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a77fab9747f6f29cf7aef17585723ceea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~FloatHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>aef925d13b8a685919b0380c9384706f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Normalize</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a75a2b864904af5a16c9562e20ff03399</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBinValueHistogramData</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a2a1aa7a746b041705349c9411a344679</anchor>
      <arglist>(int band, int bin)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InitializeWithNormalizedHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>aa12d3c528d478e39242f510573c45f8d</anchor>
      <arglist>(IntHistogram *pStandardHistogram)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InitializeWithNormalizedCumulativeHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a054ec909385eb99b5fa10419fd62cbcd</anchor>
      <arglist>(IntHistogram *pStandardHistogram, IntHistogram *pCumulativeHistogram)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeStandardKullbackLeiblerDistance</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a80c155d9fdbe36ad64c367f3c29b0efc</anchor>
      <arglist>(FloatHistogram *pOtherHistogram)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeEntropy</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a6e85a7247ea90d242be5f74e5a06377f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeSymmetricKullbackLeiblerDistance</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a30aa2cfa681e9a098aa5082cac738f82</anchor>
      <arglist>(FloatHistogram *pOtherHistogram)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeJensenShannonMetric</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a5a7e3cfd54efc7febd4601a75be3ab09</anchor>
      <arglist>(FloatHistogram *pOtherHistogram)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeIDivergence</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>ab7805e9d92a177799ffcb6976d4be79b</anchor>
      <arglist>(FloatHistogram *pOtherHistogram)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a17f4f2c1ddec4cd0e3640b2a613c3562</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEpsilonThreshold</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a4a8530c972b603231781c174f83683a9</anchor>
      <arglist>(double epsilonValue)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetEpsilonThreshold</name>
      <anchorfile>classstira_1_1histogram_1_1FloatHistogram.html</anchorfile>
      <anchor>a77d430fe9c8013091f58971d34bfeeea</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::FloodFill</name>
    <filename>classstira_1_1imageanalysis_1_1FloodFill.html</filename>
    <member kind="function">
      <type></type>
      <name>FloodFill</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>af766ba09979a908a9c636b132e896e70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>ac5ade24fbfeb218d79f8c02af8533513</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid, int nodeX, int nodeY, int targetValue, int replacementValue, bool fill8Connected=true)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; common::Point&lt; int &gt; &gt;</type>
      <name>GetFloodedPixels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>abd169a369f541b2f83abdbcadd417b6c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>common::Point&lt; double &gt;</type>
      <name>GetCenterOfGravity</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>a9bfa766a835457934962b2143db3b814</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>common::RectangularROI&lt; int &gt;</type>
      <name>GetBoundingBox</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>a73c718efa0e8f3c3184491e57767cc62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>PrepareValues</name>
      <anchorfile>classstira_1_1imageanalysis_1_1FloodFill.html</anchorfile>
      <anchor>a82569ee133765818d70593b01dc15231</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int lowerBound, int upperBound, int targetValue)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::FractalGenerator</name>
    <filename>classstira_1_1image_1_1FractalGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>FractalGenerator</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>aff285941d713a8c29db717e88518bf8b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FractalGenerator</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>aed5bd0f83395036be4ea48a01e2067e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>CreateMandelbrot</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>aedabd265d41287f43927e311d4f1f2bd</anchor>
      <arglist>(double centerX, double centerY, double width)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>CreateJulia</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>a966d1d108efcc5cd98a24c44bf8c3eef</anchor>
      <arglist>(double centerX, double centerY, double width, double Cx, double Cy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxNumberOfIterations</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>ac90a8bcc6617ff8193bc6541d63d9c87</anchor>
      <arglist>(int maxNr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEscapeRadius</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>af85a7231d3cb5a03937210a0c6438e93</anchor>
      <arglist>(double radius)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRenderDimensions</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>aeb730c164d700e57cf26b336decb6b9c</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetResolutionX</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>a4019b5af74904a0157056cdb1b730c54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetResolutionY</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>a0ecfac2195f6085749839b2e7507e2ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>common::Point&lt; double &gt;</type>
      <name>GetMathCenterPoint</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>a703e8f803f2d979bc2c00c18eac6d8f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMathWidth</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>ab093572b687616455bb183c72aef6646</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetPixelWidth</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>aae7b263f97fbe2c979031ae776732cef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetPixelHeight</name>
      <anchorfile>classstira_1_1image_1_1FractalGenerator.html</anchorfile>
      <anchor>a9d9bbc7f6487bf455c8708994f2e061a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::FunctionsOpenCV</name>
    <filename>classstira_1_1imageanalysis_1_1FunctionsOpenCV.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::filter::GaussConvolve</name>
    <filename>classstira_1_1filter_1_1GaussConvolve.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>FilterType</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a31ffc0e80910f9f3888d621483374b0c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>DerivativeType</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>af80aa2eea419506a7be13ef19ed02fff</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GaussConvolve</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>ad4694ac2ab86f3c5f2a3fc9582aa8670</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GaussConvolve</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>aaa6b2ecea5b96392fdf4bfc90b2e1991</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>CreateBlurredBars</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a550e1805ca00f5bdc2d10a5da68b251f</anchor>
      <arglist>(int width, int height, int barWidth, double sigmaBlurMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Convolve</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a8f1ce86577edb9e48e76cff469fac906</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pImage, double sigma, FilterType myType=FFT_BASED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Convolve</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a653bd29c83a85123e8b8fc2c44f5eb39</anchor>
      <arglist>(Image *pImage, double sigma, FilterType myType=FFT_BASED)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>DerivativeConvolveFFT</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a8d3eb3fb3cc53b82583b5d5da01523d0</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigmaX, double sigmaY, DerivativeType myType)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>DerivativeConvolveSeparable</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>ab95eb8e41897777902b21da57e64918b</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigma, DerivativeType myType, GridExtender&lt; double &gt;::ExtensionType myExtensionType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ConvolveSeparable</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a49a3424342c178c3f1e74dce0184ac3d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>DerivativeConvolveFFT</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>aa076a14db57b2f1c64763f3d414c4aaf</anchor>
      <arglist>(Image *pImageIn, double sigma, DerivativeType myType, GridExtender&lt; double &gt;::ExtensionType myExtensionType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>DerivativeConvolveSeparable</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a54592c449309f705d998c38539f948cb</anchor>
      <arglist>(Image *pImageIn, double sigma, DerivativeType myType, GridExtender&lt; double &gt;::ExtensionType myExtensionType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ConvolveSeparable</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a59d3a4fd2f194031983e999a0274abc0</anchor>
      <arglist>(Image *pImageIn, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianPSF</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a3a46268ab974cdc2895742f8fe0d52a3</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianPSF</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a97298935d564a17996ab83fdf557eb50</anchor>
      <arglist>(int width, int height, double sigma1, double sigma2, double rho)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>UpsampleGaussianInterpolated</name>
      <anchorfile>classstira_1_1filter_1_1GaussConvolve.html</anchorfile>
      <anchor>a9665e53f0a357e9644edd58f7946fe63</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int upscalefactor)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::GeometricTransform</name>
    <filename>classstira_1_1image_1_1GeometricTransform.html</filename>
    <member kind="function">
      <type></type>
      <name>GeometricTransform</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a9eb6d8ea03d45ffdc3f16e2facd78c54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GeometricTransform</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a52263290e5c97a0ff984b0eeaa23f581</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Apply</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a13e5da154f9aaa78e6314b647238cfe3</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>ApplyInverse</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a7349763f5829ef6de00d6d07e5a98254</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetInterpolatorType</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a91cd7ac6b6ad7df9a21654446f5594af</anchor>
      <arglist>(InterpolatorType type)</arglist>
    </member>
    <member kind="function">
      <type>InterpolatorType</type>
      <name>GetInterpolatorType</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a4e60f7f3b8a6e58beb87965ae5aec311</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual common::Point&lt; double &gt;</type>
      <name>GetTransformedPoint</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>a62673c807d2650a5676144aa881b8039</anchor>
      <arglist>(double x, double y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual common::Point&lt; double &gt;</type>
      <name>GetInverseTransformedPoint</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>af29f55482334013dda6762f62480bec1</anchor>
      <arglist>(double x, double y)=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Interpolator *</type>
      <name>mpInterpolator</name>
      <anchorfile>classstira_1_1image_1_1GeometricTransform.html</anchorfile>
      <anchor>aeb20bfc9fefdcbf1d91f79e917242a6a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::GNCDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1GNCDeconvolve.html</filename>
    <base>stira::deconvolve::IterativeDeconvolve</base>
    <member kind="function">
      <type></type>
      <name>GNCDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>aa775e9bef77c5cfa5a49116fedfc3b41</anchor>
      <arglist>(Image *pDegradedImage, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GNCDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a4dbea028c9c55176d18b60673626ab52</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GNCDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>ad0fe2ad0a101570b69e3ea68615cae5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a1f1cd0add4b8ed2a8b3a8c9fecba93bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>ae0158336a6308c493d2d8917fe72ac3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>InitializeParameters</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>aec0d262ee8d8707d2794d0662817afbd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfScales</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>ac89cbd206a499837d576afce7b1fccb1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNumberOfScales</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a6a3e7781b89198f55f6e6dc3f97ea451</anchor>
      <arglist>(int nrScales)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a9bbaf4f1eba8cbdd355e4cb1431b7a5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNumberOfOrientations</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a48a6e2abf3a401a46ec90a4cbffa901f</anchor>
      <arglist>(int nrOrientations)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMu</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a0f639cc22a4309bc3dd1c2bafd22ee48</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMu</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>ace73c3d336ce2a4fc70343b4fb44fce9</anchor>
      <arglist>(double newMu)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetLambda</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a7815399b38ed9434b26669514b859ee0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLambda</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a7fe4ca51b56c5ef349eda69374a50754</anchor>
      <arglist>(double newLambda)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetGamma</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>adfcdb25484c0a8f5b0990fce82e5780d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGamma</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>abd28587026e539e622a64655effd5027</anchor>
      <arglist>(double newGamma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetGammaFinal</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>ad4782cab514dca214e5d09a170aa55f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetGammaFinal</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a4f68be75a696c7e6dffa7064cb09d43b</anchor>
      <arglist>(double newGammaFinal)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetUpdateFactor</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a45a78bbfae4b41b0f81b54624ee6aad4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUpdateFactor</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>aa774783971a4a26a494396943d07af6e</anchor>
      <arglist>(double newFactor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMSEDifferenceThreshold</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>a44457e3f56f72bec7136f26f5f99d3a7</anchor>
      <arglist>(double myThreshold)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMSEDifferenceThreshold</name>
      <anchorfile>classstira_1_1deconvolve_1_1GNCDeconvolve.html</anchorfile>
      <anchor>af7c4e72a042de0fa2552988851fd883a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::GretagMacbethColorChecker</name>
    <filename>classstira_1_1image_1_1GretagMacbethColorChecker.html</filename>
    <member kind="function">
      <type></type>
      <name>GretagMacbethColorChecker</name>
      <anchorfile>classstira_1_1image_1_1GretagMacbethColorChecker.html</anchorfile>
      <anchor>a8d7edac84eceb1da86d26bfa3be8bf94</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GretagMacbethColorChecker</name>
      <anchorfile>classstira_1_1image_1_1GretagMacbethColorChecker.html</anchorfile>
      <anchor>adcd33bbee50e27f82f6716df3e91f7af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; ColorValue &gt;</type>
      <name>GenerateVector</name>
      <anchorfile>classstira_1_1image_1_1GretagMacbethColorChecker.html</anchorfile>
      <anchor>a3389ff0ef46f1c92328dba98e567f9f9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Generate</name>
      <anchorfile>classstira_1_1image_1_1GretagMacbethColorChecker.html</anchorfile>
      <anchor>a5f997ac3d88240f2fb4e7977506606e6</anchor>
      <arglist>(int borderWidth, int squareSize)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::simpletools::GridConverter</name>
    <filename>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</filename>
    <member kind="function">
      <type></type>
      <name>GridConverter</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</anchorfile>
      <anchor>a4f11163c75c5ea91b295a23cd287c22c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>ConvertToInt</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</anchorfile>
      <anchor>a573ccc69ddeb486c514f04ca238258cc</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>ConvertToInt</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</anchorfile>
      <anchor>a08cd85a2ef0fe75f05cfebab7a81e775</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ConvertToDouble</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</anchorfile>
      <anchor>a66f564c103f7b531e7f3b6267716a357</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pGrid, double factor=1.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ConvertToDouble</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridConverter.html</anchorfile>
      <anchor>ab82582f9d8b7eb34f73c71dd9eb9e4eb</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::simpletools::GridExtender</name>
    <filename>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>GridExtender</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>a9f3abea306415554ac8f7a13a2384988</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GridExtender</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>a8d57549a4ddcb7f891f5ab707fc3c89b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>MirrorBorder</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>a7bd8f4494fcc64aae77f3a15b777a3f4</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int borderWidth, int borderHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>PaddBorder</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>a3c4d92efed80affda5638b729ded6a8c</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int borderWidth, int borderHeight, T myValue=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>PaddBorder</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>a66b3549430358e5c0b8f3757b0b5199c</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int borderWidthLeft, int borderWidthRight, int borderHeightTop, int borderHeightBottom, T myValue=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>CropBorder</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridExtender.html</anchorfile>
      <anchor>ab076168840ec572e61bfd178c5a3508c</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int borderWidth, int borderHeight)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::GridGenerator</name>
    <filename>classstira_1_1image_1_1GridGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>GridGenerator</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>ac70eb8e2fe3b1b9ca30a315e98d258eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GridGenerator</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>ab14effb303e6763a0d072a0543801c2d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateEmpty</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>aa4e7b6597aecbfe8090c025d4f7407fc</anchor>
      <arglist>(int width=256, int height=256, double intensity=127.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateEmptyPlusGaussianNoise</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a9d01c394b9843427675bb0540fd3f550</anchor>
      <arglist>(int width=256, int height=256, double intensity=127.0, double sigma=10.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateHorizontalGradient</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a786780157c580e3f17c7dcf5fac47cfb</anchor>
      <arglist>(int width=256, int height=256)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateVerticalGradient</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a0d0e6c696f7f148f6f29a28e528cf956</anchor>
      <arglist>(int width=256, int height=256)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateHorizontalSineWave</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a3b7009c8b00b613982b703417a3e4c55</anchor>
      <arglist>(int width, int height, double frequency)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateVerticalSineWave</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a6e95b3219ca9aff2e9a8295bbb724487</anchor>
      <arglist>(int width, int height, double frequency)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateEuclideanSpots</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>adef689bab55e4b6d982d3ceb6dd90a7f</anchor>
      <arglist>(int width, int height, double frequency)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateStarChart</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a6f5d96b6c453fe743d3bc0ec4015f1ac</anchor>
      <arglist>(int sideSize, int nrPeriods)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateBars</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a0238d7c73eb8f79f4d1935355949e789</anchor>
      <arglist>(int width, int height, int barWidth=50)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateAiry</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>acdd28f8bb379c4d66fd3d777317abbdf</anchor>
      <arglist>(int width, int height, double airyWidth)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussian</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a0c8d0de48b55340dfa15c6f0fb87da3f</anchor>
      <arglist>(int width, int height, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussian</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a8434756d720e9c54a0a2725902e0bbef</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussian</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a7967f285795c57c7adcfde9c416d1929</anchor>
      <arglist>(int width, int height, double sigma1, double sigma2, double rho)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianFirstDerivativeX</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>ac26962a7bfc3e773c2d9392ac4da7134</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianFirstDerivativeY</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>af4fcb85b715504355fd8085ea5bd0aa6</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianSecondDerivativeX</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>ae50bb05372fd75924a5b9b742c0d708f</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianSecondDerivativeY</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a17d30bae2bc5e82014a8361c37b0aa9d</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianMixedDerivativesXY</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a9dd3db3719eb754b3f765e455bc5d827</anchor>
      <arglist>(int width, int height, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateDeltaPeak</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>acd2a3e206fe4bc259f928d116f6bfceb</anchor>
      <arglist>(int width, int height, int x, int y, double intensity)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateInverseZonePlate</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a046721f4f37e5eb626c0770e654ee37e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateZonePlate</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a82948ba8627ae75f0d3cc423a3e2ccf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateLogFrequencyContrastChart</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>aded3f6a05b6a0d442958268481f677c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateSheppLogan</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>afec4aa73783d12cc5925fd9f686b970c</anchor>
      <arglist>(double factor=1.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>GenerateIsingTexture</name>
      <anchorfile>classstira_1_1image_1_1GridGenerator.html</anchorfile>
      <anchor>a686f2650f66035d2f3e6b2c778877e78</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::simpletools::GridStatistics</name>
    <filename>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMinMax</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>aa8186adb6d09115087830f16f047c132</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, double &amp;mmin, double &amp;mmax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMinMax</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>ab7b4b1ec90a79a12f666c274326ee854</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, double &amp;mmin, double &amp;mmax, int &amp;xMin, int &amp;yMin, int &amp;xMax, int &amp;yMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMin</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a000290aa55d5ecc3fedf3155d034578c</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, double &amp;mmin, int &amp;xMin, int &amp;yMin)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetMax</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>ad6e5c722648ba87b08e77774f5362823</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, double &amp;mmax, int &amp;xMax, int &amp;yMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetAbsMax</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a69eeaa6ec8537ac41999601e86a92782</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetGridIntegral</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>afc7db9567a7a74142e4abcabd58dbfee</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetSquaredNorm</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a54eaf8cc7f33cd433058260e58871071</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetSquaredNorm</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>aba32dd8f1b114df74b3f591ac0ac5bc9</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetGridMean</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a1d5bca7e7c1df6e336953d116d4f5d23</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetGridVariance</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>ac3f8395e95f687e115ed38b386a90967</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, T mean)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetGridKurtosis</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a8078467e235959ec78d8eb4b03daf999</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetGridKurtosis</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a469605b3ad7a3eb8920656d2adc1c365</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, T gridMean, T gridvariance)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetLocalMinimum</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>aed60edf5e9e51ee8db4676d794fa71af</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y, int localWindowWidth, int localWindowHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetLocalMaximum</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a470f2fa127fd28308a79963fbce6cf11</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y, int localWindowWidth, int localWindowHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetLocalAbsMaximum</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a98b20fe9499e9348a25cfac7325d9407</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid, int x, int y, int localWindowWidth, int localWindowHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetLocalAbsMaximum</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a6c54f62d1e0523482a8fef65614abd80</anchor>
      <arglist>(ArrayGrid&lt; float &gt; *pGrid, int x, int y, int localWindowWidth, int localWindowHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetLocalAbsMaximum</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a8ca7f71f5d4f4a59c5d3dc3fbbb90c80</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int x, int y, int localWindowWidth, int localWindowHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>ComputeLocalMean</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>ad6f5e6cea075f39840c065a830ba6bbc</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalMean</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a92e4f13bebe364737d53139d5a415fc8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, common::RectangularROI&lt; int &gt; rroi)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalVariance</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a24c2490bd6a4571d559aa3b8c1bb61cc</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, common::RectangularROI&lt; int &gt; rroi, double thisMean)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>ComputeLocalAbsoluteMean</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>aa6eb37905edd321a8577f0ba7d5c6fa7</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalVariance</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a6c6213339d21df3793a9e69191561597</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight, double thisMean)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalVariance</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>ade714c5baca2466182875a6a2149b7ac</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalCovariance</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a9976fe4e6f19675e43859cb7dd13f134</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight, double mean1, double mean2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalKurtosis</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a99c0e971633ccc64a7b5721434af4e97</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight, double localMean, double localVariance)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalKurtosis</name>
      <anchorfile>classstira_1_1imagedata_1_1simpletools_1_1GridStatistics.html</anchorfile>
      <anchor>a0f177764b09eb7d645c9a5aa482f1c04</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int &amp;xTopLeft, int &amp;yTopLeft, int &amp;xBottomRight, int &amp;yBottomRight)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::contrastenhance::HazeRemover</name>
    <filename>classstira_1_1contrastenhance_1_1HazeRemover.html</filename>
    <member kind="function">
      <type></type>
      <name>HazeRemover</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HazeRemover.html</anchorfile>
      <anchor>ae1340173809db5b688201235d317924d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~HazeRemover</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HazeRemover.html</anchorfile>
      <anchor>a3933fa187f1c312d8dc785be847d09d3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HazeRemover.html</anchorfile>
      <anchor>a3fcd3688b4f30325e805ebfa1251f0f3</anchor>
      <arglist>(Image *pImage)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>histList</name>
    <filename>structhistList.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::histogram::HistogramMaster</name>
    <filename>classstira_1_1histogram_1_1HistogramMaster.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type>void</type>
      <name>AddDataPoint</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>adb70bc2af57d40a17e050c604da824c2</anchor>
      <arglist>(int valueToAdd, int bandNr=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinsToZero</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7ea892f70126c65b1db8adf2887a537f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>abf6d7ad6388d45fe2292cc9098bc71aa</anchor>
      <arglist>(int bandNr, int binNr) const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a82f793383345504f8316d8608a9925a1</anchor>
      <arglist>(int bandNr, int binNr) const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a53db7f0f7245aefb9c5b1ba2fae2e12d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>aaf98d78c9b2b983458caa1c966e3e3f5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7812e1c4cb4eb3b978635308c1fa9566</anchor>
      <arglist>(std::string fileName)=0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a46b51fe4a340409d9e66c28f9b6fa39d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a26a107cfb34a58080e3be28dfcdb549b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetDataMinimum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ae76269853c5f82e13ab2ab03f3cb465b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetDataMaximum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a78604780cfeaf25413db7bf8237d5e75</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a98d42471863ac028917a9076378479d2</anchor>
      <arglist>(int bandNr, int binNr, T value)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a9411d3b669d7a1e37e14f2bab8daa793</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>af9fa388fb9a8c171a38ce1fc2cd84a14</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a230ee8aacdd8d2b04a982dacce8ad38c</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a147e8a47021f383a99528faa97fd7bbe</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ac174954cda91364c68081dfbdc6eaa73</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a00c35f5895400512b9475bf73767f211</anchor>
      <arglist>(const HistogramMaster &amp;pHistogram)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a746bffe56091f4ae819a5e69dfe18bca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a96614ad6c6b750898a3644b2c4c3d747</anchor>
      <arglist>(T binSize, int nrOfBands, T minValue, T maxValue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateInitializedDataStructure</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a712fe3e14dbf2dbada5d5d706b74139e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ade0ccfd49edfcb7bca1aa9c607d0ec62</anchor>
      <arglist>(int bandNr, int binNr, T value)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T **</type>
      <name>mpHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a62d2e789de053e4594f20fd294366572</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>mBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a764d3260febb856b43b7553d42992ec6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a346468de6e9ad255890281ec8288fff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7837ee726968e12b7324f5b1a6d74203</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a35e8423bd68ac3a5289b1e0256af83af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>mMin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a0ccb35564b76d4b05f2b71319d49cd27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>T</type>
      <name>mMax</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a4e3fe37b514933fc14abe5e458632cb4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>HistogramMaster&lt; double &gt;</name>
    <filename>classstira_1_1histogram_1_1HistogramMaster.html</filename>
    <member kind="function">
      <type>void</type>
      <name>AddDataPoint</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>adb70bc2af57d40a17e050c604da824c2</anchor>
      <arglist>(int valueToAdd, int bandNr=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinsToZero</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7ea892f70126c65b1db8adf2887a537f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>abf6d7ad6388d45fe2292cc9098bc71aa</anchor>
      <arglist>(int bandNr, int binNr) const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a82f793383345504f8316d8608a9925a1</anchor>
      <arglist>(int bandNr, int binNr) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a53db7f0f7245aefb9c5b1ba2fae2e12d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>aaf98d78c9b2b983458caa1c966e3e3f5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7812e1c4cb4eb3b978635308c1fa9566</anchor>
      <arglist>(std::string fileName)=0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a46b51fe4a340409d9e66c28f9b6fa39d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a26a107cfb34a58080e3be28dfcdb549b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDataMinimum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ae76269853c5f82e13ab2ab03f3cb465b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDataMaximum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a78604780cfeaf25413db7bf8237d5e75</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a98d42471863ac028917a9076378479d2</anchor>
      <arglist>(int bandNr, int binNr, doublevalue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a9411d3b669d7a1e37e14f2bab8daa793</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a230ee8aacdd8d2b04a982dacce8ad38c</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>af9fa388fb9a8c171a38ce1fc2cd84a14</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a147e8a47021f383a99528faa97fd7bbe</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ac174954cda91364c68081dfbdc6eaa73</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a00c35f5895400512b9475bf73767f211</anchor>
      <arglist>(const HistogramMaster &amp;pHistogram)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a746bffe56091f4ae819a5e69dfe18bca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a96614ad6c6b750898a3644b2c4c3d747</anchor>
      <arglist>(doublebinSize, int nrOfBands, doubleminValue, doublemaxValue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateInitializedDataStructure</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a712fe3e14dbf2dbada5d5d706b74139e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ade0ccfd49edfcb7bca1aa9c607d0ec62</anchor>
      <arglist>(int bandNr, int binNr, doublevalue)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double **</type>
      <name>mpHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a62d2e789de053e4594f20fd294366572</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a764d3260febb856b43b7553d42992ec6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a346468de6e9ad255890281ec8288fff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7837ee726968e12b7324f5b1a6d74203</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a35e8423bd68ac3a5289b1e0256af83af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mMin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a0ccb35564b76d4b05f2b71319d49cd27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mMax</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a4e3fe37b514933fc14abe5e458632cb4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>HistogramMaster&lt; int &gt;</name>
    <filename>classstira_1_1histogram_1_1HistogramMaster.html</filename>
    <member kind="function">
      <type>void</type>
      <name>AddDataPoint</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>adb70bc2af57d40a17e050c604da824c2</anchor>
      <arglist>(int valueToAdd, int bandNr=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinsToZero</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7ea892f70126c65b1db8adf2887a537f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>abf6d7ad6388d45fe2292cc9098bc71aa</anchor>
      <arglist>(int bandNr, int binNr) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a82f793383345504f8316d8608a9925a1</anchor>
      <arglist>(int bandNr, int binNr) const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a53db7f0f7245aefb9c5b1ba2fae2e12d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>aaf98d78c9b2b983458caa1c966e3e3f5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7812e1c4cb4eb3b978635308c1fa9566</anchor>
      <arglist>(std::string fileName)=0</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a46b51fe4a340409d9e66c28f9b6fa39d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a26a107cfb34a58080e3be28dfcdb549b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetDataMinimum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ae76269853c5f82e13ab2ab03f3cb465b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetDataMaximum</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a78604780cfeaf25413db7bf8237d5e75</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a98d42471863ac028917a9076378479d2</anchor>
      <arglist>(int bandNr, int binNr, intvalue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a9411d3b669d7a1e37e14f2bab8daa793</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a230ee8aacdd8d2b04a982dacce8ad38c</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>af9fa388fb9a8c171a38ce1fc2cd84a14</anchor>
      <arglist>(int bandNr, int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AddOneToBinSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a147e8a47021f383a99528faa97fd7bbe</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ac174954cda91364c68081dfbdc6eaa73</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a00c35f5895400512b9475bf73767f211</anchor>
      <arglist>(const HistogramMaster &amp;pHistogram)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~HistogramMaster</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a746bffe56091f4ae819a5e69dfe18bca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a96614ad6c6b750898a3644b2c4c3d747</anchor>
      <arglist>(intbinSize, int nrOfBands, intminValue, intmaxValue)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CreateInitializedDataStructure</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a712fe3e14dbf2dbada5d5d706b74139e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetBinValueSafe</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>ade0ccfd49edfcb7bca1aa9c607d0ec62</anchor>
      <arglist>(int bandNr, int binNr, intvalue)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int **</type>
      <name>mpHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a62d2e789de053e4594f20fd294366572</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mBinSize</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a764d3260febb856b43b7553d42992ec6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBands</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a346468de6e9ad255890281ec8288fff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfBins</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a7837ee726968e12b7324f5b1a6d74203</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOfCounts</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a35e8423bd68ac3a5289b1e0256af83af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mMin</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a0ccb35564b76d4b05f2b71319d49cd27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mMax</name>
      <anchorfile>classstira_1_1histogram_1_1HistogramMaster.html</anchorfile>
      <anchor>a4e3fe37b514933fc14abe5e458632cb4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::contrastenhance::HistogramTools</name>
    <filename>classstira_1_1contrastenhance_1_1HistogramTools.html</filename>
    <member kind="function">
      <type></type>
      <name>HistogramTools</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>af4951e067ccb89470aab703ce4180c99</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~HistogramTools</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>a2f445b012df487ba7dc7265425352773</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>RemapHistogramInROI</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>aa5eb0d0d722c2a6cf7f72030cac34c45</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInGrid, common::RectangularROI&lt; int &gt; rroi, histogram::IntHistogram *fhCumulativeInput, histogram::FloatHistogram *fhCumulativeReference)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>MatchHistogramValue</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>a6d4596f3a6a6ef2c08da5e6956f0d0f8</anchor>
      <arglist>(double inValue, histogram::IntHistogram *fhIncomingCumulativeHistogram, histogram::FloatHistogram *fhCumulativeReferenceHistogram)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RobustLinearRescale</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>abeb969472aca7f26aaf56954551c2d25</anchor>
      <arglist>(Image *pSourceImage, double lowerFraction=0.01, double upperFraction=0.99)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>RobustLinearRescaleNoNew</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>ace6b8371916b276ced4c2a2792aa6927</anchor>
      <arglist>(Image *pSourceImage, double lowerFraction=0.01, double upperFraction=0.99)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>HistogramEqualizeSingleBand</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>a0e33572a06c1da9b908907ca12a72fd1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInOutGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>HistogramEqualizePerBand</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>a7ba7b133fb495eebe54fc97e3732af55</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>HistogramEqualizeHSI</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>ab90a86d3f9df1fa21055af194a5bc93c</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ColorHistogramEqualize</name>
      <anchorfile>classstira_1_1contrastenhance_1_1HistogramTools.html</anchorfile>
      <anchor>a0c2f7e5f25255fad909ed4adb57eb5dc</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::HOG</name>
    <filename>classstira_1_1imageanalysis_1_1HOG.html</filename>
    <member kind="function">
      <type></type>
      <name>HOG</name>
      <anchorfile>classstira_1_1imageanalysis_1_1HOG.html</anchorfile>
      <anchor>a587f87f3659fc1376c15efa4422b6dd1</anchor>
      <arglist>(Image *pImage, common::RectangularROI&lt; int &gt; myRoi, int cellWidth, int cellHeight, int nrBins)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ComputeHogDescriptor</name>
      <anchorfile>classstira_1_1imageanalysis_1_1HOG.html</anchorfile>
      <anchor>aa01da0cf003ca9e930467e7122ece455</anchor>
      <arglist>(std::vector&lt; double &gt; &amp;descriptorValues)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>VisualizeHogDescriptor</name>
      <anchorfile>classstira_1_1imageanalysis_1_1HOG.html</anchorfile>
      <anchor>a5346a7d6c2914eb37a3b871e36c6e8e1</anchor>
      <arglist>(std::vector&lt; double &gt; &amp;descriptorValues, int winWidth, int winHeight, double scaleFactor, double viz_factor)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::HoughTransform</name>
    <filename>classstira_1_1imageanalysis_1_1HoughTransform.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::Image</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1Image.html</filename>
    <member kind="function">
      <type></type>
      <name>Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a457bfa3d78b9732ea957580fe4503128</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a907472ec782381707c17f7335a417d02</anchor>
      <arglist>(int width, int height, int nrBands)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>adfae258473eeb640236a4af755152be4</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pDataGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4e7f1cb0ed65c3374467b2fd2fb7e519</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pBoolGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ac0e8426c33db2958637907ac00b8c4cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>GetImageName</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4ffde3e637a2cced7a053a5f69dadaab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetImageName</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a087285f4b765dfb3b7d3d99665bd6bbc</anchor>
      <arglist>(std::string imagename)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4bf9883ef88d5213c2a907c72502df97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Image</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>af73f32c2b91b0d0b5494aa58a1e94286</anchor>
      <arglist>(Image &amp;otherImage)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>ExtractROIAsNewImage</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ade67c779a1d752acd0adc18118334d6c</anchor>
      <arglist>(common::RectangularROI&lt; int &gt; rroi)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>InsertSubImage</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a2c01511a3e739ddfbfbb99a6b063852b</anchor>
      <arglist>(Image *pSubImage, int xTop, int yTop)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>abead3c7c0ecae505ef84cfe6f1205af3</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4663870d8042837b710805334f31197a</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aa055ad4a2b201dad5a9c297c60b70e04</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReplaceBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4c5ec20653807cb39a5e5d58bdb82746</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBandOld, ArrayGrid&lt; double &gt; *pBandNew)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; ArrayGrid&lt; double &gt; * &gt; &amp;</type>
      <name>GetBands</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a866841caa90b75af31725dd3173e76f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ad2878f8d65ef3f198fb2fcb46ff7c168</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>adfcd8d72eee3de12bf7b60f8bee13223</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfBands</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ad7fb0657193b587d0d90599847da919c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetMinMax</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ae6541fa7a36deb34800d8c96245f6ae0</anchor>
      <arglist>(double &amp;outMin, double &amp;outMax, int &amp;minBandNr, int &amp;maxBandNr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>GetMinMax</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a515bc2411dfcdf6d12ad1516792f5ad5</anchor>
      <arglist>(double &amp;outMin, double &amp;outMax)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAbsMax</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a440504a5809526ac46f914e5654bc022</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Rescale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a9fffd0d99bf3d8c21725cb0d2cb2ac65</anchor>
      <arglist>(double mmin=0.0, double mmax=255.0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyImageValues</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a6ab02af99686c7d721277280f5bca981</anchor>
      <arglist>(Image *pOtherImage)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MultiplyWith</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>acab27fc9e562e538018d16f2e35fd522</anchor>
      <arglist>(Image *pImg)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Scale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>acb3b76f7dbb94d749240cb75626fb5ea</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddGaussianNoise</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a8505b1982d4688b3eee919024630a5bc</anchor>
      <arglist>(double sigma, bool isColored=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyPoissonNoise</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a2fb5a9bb9203de7bb9b714397d772943</anchor>
      <arglist>(double factor, bool isColored=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplySaltAnPepperNoise</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aeb55588fe71ed909f40aed28636a6fa9</anchor>
      <arglist>(double fraction, bool isColored=true)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>GetColor</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a5ccf73a7fd2fe0c20e14a788f3c2192c</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>GetColor</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a0b972217bb5ff11260866a9b27dc232b</anchor>
      <arglist>(common::Point&lt; int &gt; pt)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetColor</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>af9488b5040ff6017d4f308aaeeea0313</anchor>
      <arglist>(int x, int y, ColorValue cv)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetColor</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a597b184cbc0675d2c743e10b770cfe8b</anchor>
      <arglist>(common::Point&lt; int &gt; pt, ColorValue cv)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HSVToRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a8f2e5641da548a7c9b9883ac24a03ca0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RGBToHSV</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ab36bd19796e029d10f2d73c40913670a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HSIToRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aa33714d789c412476b49c1bd285bb8e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RGBToHSI</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a0348a221eaf889b5e1397236092023c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HSLToRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a34ed07bcd0ddaa8d18c4bc1b489b6591</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RGBToHSL</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a3fe099d0173d5807dc49387af10b99d0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sRGBToXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ab1fe0b28dcf2656015da94039d3450a2</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>XYZTosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ab5fd8fba3b17ea70450d02fddff94702</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>AdobeRGBToXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a9840cdc5dffe6d47d6c5d3963bafc340</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>XYZToAdobeRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a4be5190740be77e323d3ea04bfbab088</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sRGBToLuv</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a67a7fbfe1d60f4ce8c2f550ef8ad487a</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LuvTosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aca463c625da59e623de9e0728aa3ff11</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>sRGBToLab</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aa485b41d94d8be2bcf30235a973a2117</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>LabTosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aa83684cc56ed0d6113b54fda254b3a4c</anchor>
      <arglist>(ColorValue referenceIlluminant=ColorConstants::sD65_XYZ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RGBToYUV</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a145f2eb137ef3919fb5ce2c86fb21a0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>YUVToRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>a29eb6c70df15a5715deaee5c99262893</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>RGBToCMY</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>aa6cc5b71735edc90fc8bbffaa2b52278</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CMYToRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Image.html</anchorfile>
      <anchor>ac0243a4f624eda878ddfea3d818baa2b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::ImageIO</name>
    <filename>classstira_1_1image_1_1ImageIO.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>outputType</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NULL_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a8aa81c04cfc362815324223324358033</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GRADIENT_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695ac0e950a1666afa8c801d50d38b46fc4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NORMAL_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a70fe407aeead94be93489b08bee93892</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LOG_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a0b9eae918d187a75cc3e82d4dfa837b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_NORM_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a7b123394b27167f7869e9970cfd6242c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_POS_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a73653c029a1c4c3bed901a82aa567172</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_NEG_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695ab7517a5d6846bcdd840598114965bea8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NULL_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a8aa81c04cfc362815324223324358033</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>GRADIENT_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695ac0e950a1666afa8c801d50d38b46fc4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NORMAL_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a70fe407aeead94be93489b08bee93892</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LOG_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a0b9eae918d187a75cc3e82d4dfa837b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_NORM_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a7b123394b27167f7869e9970cfd6242c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_POS_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695a73653c029a1c4c3bed901a82aa567172</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ABSOLUTE_NEG_OUT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad0b90f451dcdde1070a6cd25ff528695ab7517a5d6846bcdd840598114965bea8</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ImageIO</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a979470b3fd0deee7b0eba3ff35e0f57f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ImageIO</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ab0dbbf15848c4bf75b5801bb86300c8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Read</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ab9b1726648d55d8dac28d20e9111c697</anchor>
      <arglist>(std::string fname)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>ReadPGMasInt</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ae14245b5913ce7bc84eeebf6201dc5d4</anchor>
      <arglist>(std::string fname)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>af8c85b2046c8a43e63421fef8b6cdbe7</anchor>
      <arglist>(Image *pImage, std::string fname, outputType outtype=NULL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>WritePGM</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a9d1352b8aa3c5722bd156466b00b166c</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGrid, std::string fileName, outputType outtype=NULL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WritePGM</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a64078bfb182af20af242f686eb88eb5a</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, std::string fileName, outputType outtype=NULL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WritePGM</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a8e609fbcf2cc7a25bdb83b8855fbf79a</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid, std::string fileName, outputType outtype=NULL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WritePGM</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>abec3ac89d90d261f0a6dcf6c55bd2b50</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pGrid, std::string fileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WriteTXT</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a53f74fb30382f540d89449b36ca747ba</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, std::string fileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetOpenCvGrayValue</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a3e258c7156404ef2a5872365bcbe34cb</anchor>
      <arglist>(IplImage *pIplImage, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetOpenCvGrayValue</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a428ef9db8f830dfc2cd56bd0efd52d6a</anchor>
      <arglist>(IplImage *pIplImage, int x, int y, double value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetOpenCvColorValue</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>aee5ddf0a1f52ab5bede08e9d7e398caa</anchor>
      <arglist>(IplImage *pIplImage, int x, int y, int bandNr)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SetOpenCvColorValue</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a9402029c96cb605920560c69a929f35a</anchor>
      <arglist>(IplImage *pIplImage, int x, int y, int bandNr, double value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ConvertOpenCvToImage</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a1a212f20fe0dfa714f053584454eb0e3</anchor>
      <arglist>(IplImage *pIplImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IplImage *</type>
      <name>ConvertImageToOpenCv</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a0be711d0effc9b7984ec7c5ea3c14759</anchor>
      <arglist>(Image *pImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ReadImageOpenCV</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a45e4026b32b544e33d0d2923f369b6b9</anchor>
      <arglist>(std::string fname, bool useROI=false, common::RectangularROI&lt; int &gt; myImageROI=common::RectangularROI&lt; int &gt;(0, 0, 0, 0))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ReadArrayOpenCVAsDouble</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a0c2edd6526c9624c4a41d218e4d9eb9c</anchor>
      <arglist>(std::string fname, ArrayGrid&lt; double &gt; *pGrid=0, bool useROI=false, common::RectangularROI&lt; int &gt; myImageROI=common::RectangularROI&lt; int &gt;(0, 0, 0, 0))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>ReadArrayOpenCVAsInt</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a15f96b0d7ad2adc7e7a2d75b140c8333</anchor>
      <arglist>(std::string fname, bool useROI=false, common::RectangularROI&lt; int &gt; myImageROI=common::RectangularROI&lt; int &gt;(0, 0, 0, 0))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WriteOpenCV</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a952eee6cc8cb6edf5c3a1ef2d1198dfe</anchor>
      <arglist>(Image *pImage, std::string fname, outputType outtype=NORMAL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WriteOpenCV</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>afed371f406a213663748cba4df10a614</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, std::string fname, outputType outtype=NORMAL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WriteOpenCV</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>afd25bb0f670bf7c02d5fba6907e2e646</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid, std::string fname, outputType outtype=NORMAL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>WriteOpenCV</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a5b6eaefb748c774aaca132749c788c9c</anchor>
      <arglist>(ArrayGrid&lt; bool &gt; *pGrid, std::string fname)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GetInputMinMax</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>ad67cc602d7cc1c43d2295eb502dd809f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double &amp;mmin, double &amp;mmax, outputType myType=NULL_OUT)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>RescaleGrid</name>
      <anchorfile>classstira_1_1image_1_1ImageIO.html</anchorfile>
      <anchor>a1daa9ab7629a58a832cee3eab39999b2</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, outputType outtype=NULL_OUT)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::simpletools::ImageStatistics</name>
    <filename>classstira_1_1imagedata_1_1simpletools_1_1ImageStatistics.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::image::ImageTools</name>
    <filename>classstira_1_1image_1_1ImageTools.html</filename>
    <member kind="function">
      <type></type>
      <name>ImageTools</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>aed903e3c3ec025a5605b374c40794643</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ImageTools</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a9e31ab00697afe87bb08a5f9cd48fdc9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>MirrorBorder</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ac9ae211098764c3ab184b53de26ebc3c</anchor>
      <arglist>(Image *pInImage, int borderWidth, int borderHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CropBorder</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ab948d274d889013d96b4d3d2c842456a</anchor>
      <arglist>(Image *pInImage, int borderWidth, int borderHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>PaddBorder</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a782f226a6df2274b48737c55000f1f3a</anchor>
      <arglist>(Image *pInImage, int borderWidth, int borderHeight, double paddingValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ExtractSubImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ae6b10e366bd733f8e4c8e8180b9515fa</anchor>
      <arglist>(Image *pInImage, common::Point&lt; int &gt; topLeft, common::Point&lt; int &gt; bottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>InsertSubGrid</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a1e7fc6a1306436170c24bc96b20fcb04</anchor>
      <arglist>(Image *pImage, ArrayGrid&lt; double &gt; *pSubGrid, int xTop, int yTop)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ad05c416141951fac0aa6fc7b84adac0f</anchor>
      <arglist>(Image *pImage, std::string ID=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateImageSSD</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>aa0ace5c46b24ffeab328d2dbcb7e8d24</anchor>
      <arglist>(Image *pImage1, Image *pImage2, bool printOutput=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeMSE</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a3d18eb3e9a737bdbaf51b7bf5be4c59b</anchor>
      <arglist>(Image *pImage1, Image *pImage2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputePSNR</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ac6752c35ab51e0c236c0dde29673592e</anchor>
      <arglist>(Image *pImage1, Image *pImage2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateImageSSIM</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>aeef58b927169febdee36c30a083814a9</anchor>
      <arglist>(Image *pImage1, Image *pImage2, int localWindowSize=9)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; double &gt;</type>
      <name>GetColorMappingFactors</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a1a90244293d6b666bf2de9aa0f220f2d</anchor>
      <arglist>(Image *pImage1, Image *pImage2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateCheckeredImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a99d179972967fd476422b310ee6ced9c</anchor>
      <arglist>(Image *pImage1, Image *pImage2, int blockSize=35)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateTransparantlyMixedImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>aa6a212a380e586b3b12651d589e72f81</anchor>
      <arglist>(Image *pImage1, Image *pImage2, double thisWeight=0.5)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ApplyGamma</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a52c6ef03d986c48675cfd3e83f7c1740</anchor>
      <arglist>(Image *pInImage, double gamma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateLinearRescaledImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a2fc88f6c9922b8b4a7c349e272e7dc03</anchor>
      <arglist>(Image *pImage, bool bandsIndependent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ApplyJetColorMap</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a1a71afb454ae73eadc022a34ee3c39c9</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ConvertToGrayImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ae98a8694e5bdf8ac612da8108f07df2a</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>ConvertToSepiaImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>afa96eeed9ab421b28095e4de1d547fb7</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Negative</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a09d86fc3c6844614c64bb09cbd9e6296</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Rotate90DegreesClockwise</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a2d4a7fbddfe1c99243918437df5aad1a</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Rotate90DegreesCounterClockwise</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a36a51fbf4779da78e2f52e7079714aed</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Rotate180Degrees</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a0f59a739c33c019c47d541f4f4e0e97a</anchor>
      <arglist>(Image *pInImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetLocalDarkChannel</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>aafa5e479805ef1195f6a8a4c32c75ffd</anchor>
      <arglist>(Image *pImage, int xLocalCenter, int yLocalCenter, int windowSize)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned int *</type>
      <name>CreateIntArrayFromColorImage</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>ae547d666a2231fb48aa5c44e8e28e148</anchor>
      <arglist>(Image *pImage)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>CreateColorImageFromIntArray</name>
      <anchorfile>classstira_1_1image_1_1ImageTools.html</anchorfile>
      <anchor>a95122c0b6ecab5d2588bb5d054832e64</anchor>
      <arglist>(unsigned int *pIntArray, int width, int height)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::IntensityPoint</name>
    <filename>structstira_1_1common_1_1IntensityPoint.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::image::Interpolator</name>
    <filename>classstira_1_1image_1_1Interpolator.html</filename>
    <member kind="function">
      <type></type>
      <name>Interpolator</name>
      <anchorfile>classstira_1_1image_1_1Interpolator.html</anchorfile>
      <anchor>afa49b2ac25be93d5cbb0c877b1d2a469</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Interpolator</name>
      <anchorfile>classstira_1_1image_1_1Interpolator.html</anchorfile>
      <anchor>a905e8019fdfcbe4171a12808a9ad8527</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1image_1_1Interpolator.html</anchorfile>
      <anchor>ad2dc948fc55bc63f3c6c08ace8ce4c95</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double x, double y)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::histogram::IntHistogram</name>
    <filename>classstira_1_1histogram_1_1IntHistogram.html</filename>
    <base>HistogramMaster&lt; int &gt;</base>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a33e4913756e86fd8b905b2b7c2cc443d</anchor>
      <arglist>(Image *pImage, bool useDataMinMax, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1, ArrayGrid&lt; bool &gt; *pMaskGrid=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a3020f32bdb8e241c77da6af64f85d07c</anchor>
      <arglist>(Image *pImage, bool useDataMinMax, common::RectangularROI&lt; int &gt; rroi, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a40e39dfe48e1224d7bc310e27f5cf57f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, bool useDataMinMax, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1, ArrayGrid&lt; bool &gt; *pMaskGrid=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a11d45ec8084c10dce66992bcc198f419</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, bool useDataMinMax, common::RectangularROI&lt; int &gt; rroi, double lowerFraction=0.01, double upperFraction=0.99, int binsize=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a7502c52b94ab537f010c2b469a4d3e05</anchor>
      <arglist>(double binSize, int nrOfBands, int minValue, int maxValue, double lowerFraction=0.01, double upperFraction=0.99)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>ad3b663362812717dc7d69998ca3be60c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>IntHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>af27f53c7ee8dff6a7c3f2ad42b8e2ad0</anchor>
      <arglist>(const IntHistogram &amp;pHistogram)</arglist>
    </member>
    <member kind="function">
      <type>IntHistogram *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a313a242bb08c3db3e1fd4219f7ca20bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetLowerFraction</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>ab66088d3c65c38f0add11a15a6c7bdae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowerFraction</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a4733cf8eb37ffe9c663a7a0c914fe4bd</anchor>
      <arglist>(double myFraction)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetLowerBound</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a917020c9af782126a4561fb94c2e28bc</anchor>
      <arglist>(int bandNr=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetUpperFraction</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>afbef922792ff552f9f7e3bc5ce7f1df5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUpperFraction</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>acbaf61bc50855f885280eb9bc3e903c2</anchor>
      <arglist>(double myFraction)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetUpperBound</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>ab0e7e137b92879b3f52213bdea90d1f8</anchor>
      <arglist>(int bandNr=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetQuantile</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a12e0ad0d01092367b1c25046561e618d</anchor>
      <arglist>(int bandNr, double probability)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ConvertInCumulativeHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>a1ab1e9c475fdc3cc9db62e196844761f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>af16a85e970136e96f5e41280f00227ab</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>DetermineBounds</name>
      <anchorfile>classstira_1_1histogram_1_1IntHistogram.html</anchorfile>
      <anchor>ae5a0ec9226d8fc446de94947e27b2a91</anchor>
      <arglist>(int bandNr=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::IterativeDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</filename>
    <base>stira::deconvolve::DeconvolveMaster</base>
    <member kind="function">
      <type>void</type>
      <name>SetLambda</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>ab710c93455c23774638db47f89b068f8</anchor>
      <arglist>(double lambda)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetLambda</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a267089333478d012085cac9172bbdf40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetStepSize</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a94f2654b8964fc840d8b1e4bb74d537b</anchor>
      <arglist>(double stepSize)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetStepSize</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>ac43b37d35436bcbf3f6d02e292f28525</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetMaximumNrOfIterations</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a20e9840663d73c8048217fd1d94c7c88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaximumNrOfIterations</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a5cf8137c95e694221cc08811d5eb6176</anchor>
      <arglist>(int nrIter)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>IterativeDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a6fb8203b7610a87c707b5fdac9e6e352</anchor>
      <arglist>(Image *pDegradedImage, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>IterativeDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a76da3dc69eaedf007d8c854f669f1b7c</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~IterativeDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a50847628ffdbba558552767e577a08ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a525b99380fca951bdc062c665e3b943a</anchor>
      <arglist>(int maxNrOfIterations)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>PrepareCurrentGrids</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a2de16c78babcea3503a8c0b521a35504</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>RunSingleIterationSingleBand</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a9af02212e86aa09f70ddec605cc81229</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image *</type>
      <name>mpLastEstimate</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a74553d55ffa79ff0fe14c24a32a64e74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Image *</type>
      <name>mpNewEstimate</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a1295819abe30d0d84d44021578562744</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mLambda</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>ae28d76b410d2e40d71ff70cfdcfe82f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mStepSize</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a0a7da6e73c669dc5e20bcc3a4db25c2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentIterationNr</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>ac90a25eca04cb876fcf03b61d9a0fb5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentBandNr</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>ace005ec0c57861861871d54bb741516d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mMaximumNrOfIterations</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a1cd9464d5315e3dcfec46864d1822c34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpDegradedGrid</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>a35afed3ee15e6833ad0026a067511c0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpLastGrid</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>aba76e769d1f65fe749cb031c04e27e65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpNewGrid</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>afdf2eb65612e03b1f0a457f0c93126e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpPSFGrid</name>
      <anchorfile>classstira_1_1deconvolve_1_1IterativeDeconvolve.html</anchorfile>
      <anchor>aeab86178dee57af23701e7870e8feb32</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::histogram::JointHistogram</name>
    <filename>classstira_1_1histogram_1_1JointHistogram.html</filename>
    <member kind="function">
      <type></type>
      <name>JointHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>ae14ed96ead79b53acb1bac4ef562955e</anchor>
      <arglist>(double horizontalBinSize, double verticalBinSize, double horizontalMin, double horizontalMax, double verticalMin, double verticalMax, int nrBands=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JointHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>aee99e2ec3a8d4c92f18381b5e9870709</anchor>
      <arglist>(Image *pImage1, Image *pImage2, bool useAbsoluteValues=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JointHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>a06d789d540b355fba04bbb9f20f70f0b</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1, ArrayGrid&lt; double &gt; *pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2, bool useAbsoluteValues=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>JointHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>a76efd3a4a14bc9420dfcac8491eb20c8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, bool useAbsoluteValues=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~JointHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>a4b90364e87a7dc4a38a9dcef6be73db9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>a163f5369af47beb9d8d558a328c50445</anchor>
      <arglist>(std::string fileName)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfHorizontalBins</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>ac8a6a7531aabd7a03a21b39c4798c471</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNrOfVerticalBins</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>a56b627207c93acfadfbead2bbe6ce276</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>VisualizeAsImage</name>
      <anchorfile>classstira_1_1histogram_1_1JointHistogram.html</anchorfile>
      <anchor>adca4b57c72e0591197344ba699819c9a</anchor>
      <arglist>(std::string imageName)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>kiss_fft_cpx</name>
    <filename>structkiss__fft__cpx.html</filename>
  </compound>
  <compound kind="struct">
    <name>kiss_fft_state</name>
    <filename>structkiss__fft__state.html</filename>
  </compound>
  <compound kind="struct">
    <name>kiss_fftnd_state</name>
    <filename>structkiss__fftnd__state.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::KISSFFTCalculator</name>
    <filename>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</filename>
    <base>stira::fouriertools::FFTCalculator</base>
    <member kind="function">
      <type></type>
      <name>KISSFFTCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</anchorfile>
      <anchor>adca3986e2d72ca5772a8f0b68f9104bc</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pComplexGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KISSFFTCalculator</name>
      <anchorfile>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</anchorfile>
      <anchor>aa7f735359c00f8787150d436a919f1a4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyForwardTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</anchorfile>
      <anchor>a25f33449a1f847c54fa6fff08b50814e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ApplyInverseTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</anchorfile>
      <anchor>a090f2245fbf2e7287ca489696cef4d09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>ApplyInverseTransform</name>
      <anchorfile>classstira_1_1fouriertools_1_1KISSFFTCalculator.html</anchorfile>
      <anchor>a307984e4a8874ab6870106503260f18f</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::KuwaharaFilter</name>
    <filename>classstira_1_1filter_1_1KuwaharaFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>KuwaharaFilter</name>
      <anchorfile>classstira_1_1filter_1_1KuwaharaFilter.html</anchorfile>
      <anchor>aeed1144feb7bc23b53f1e930a10c710b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~KuwaharaFilter</name>
      <anchorfile>classstira_1_1filter_1_1KuwaharaFilter.html</anchorfile>
      <anchor>a86e675cd97ef10cd82434c45444b3659</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1KuwaharaFilter.html</anchorfile>
      <anchor>a676ca865114794ff3e0319214178446c</anchor>
      <arglist>(Image *pImageIn, int windowSize=5)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>GetSmallestIndex</name>
      <anchorfile>classstira_1_1filter_1_1KuwaharaFilter.html</anchorfile>
      <anchor>a21df0b6e6973acfcf567a78ebae208ee</anchor>
      <arglist>(double *pArray, int size)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::imagedata::color::lab_t</name>
    <filename>structstira_1_1imagedata_1_1color_1_1lab__t.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>l</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lab__t.html</anchorfile>
      <anchor>a1113dd6c2f43c9ed23e6e9c57851f8ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>a</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lab__t.html</anchorfile>
      <anchor>a5f476bc8bdd080ff72e23215fca646b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>b</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lab__t.html</anchorfile>
      <anchor>acdf743068308e5956e451024300ea4d0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::LaplacianOfGaussianFilter</name>
    <filename>classstira_1_1filter_1_1LaplacianOfGaussianFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>LaplacianOfGaussianFilter</name>
      <anchorfile>classstira_1_1filter_1_1LaplacianOfGaussianFilter.html</anchorfile>
      <anchor>a201f2d84f26884694453a4c7759e1644</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LaplacianOfGaussianFilter</name>
      <anchorfile>classstira_1_1filter_1_1LaplacianOfGaussianFilter.html</anchorfile>
      <anchor>a657d08e08eb28d3bef28ac5dd781bc67</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1LaplacianOfGaussianFilter.html</anchorfile>
      <anchor>a90cd231dd9ea47d9dd77e2e121f19fa6</anchor>
      <arglist>(Image *pImage, double scaleFactor=1.0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::LineSegment</name>
    <filename>classstira_1_1common_1_1LineSegment.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>LineSegment</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>a71e8fd72c745b20f51681ca19ce34997</anchor>
      <arglist>(Point&lt; T &gt; point1, Point&lt; T &gt; point2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LineSegment</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>a466fd93ade77c28079829f9751cba532</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>GetPoint1</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>ac93a9d2e52012fef2e0079ba7514d651</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPoint1</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>a9c2b9298c69b9277286bab3825c2c33a</anchor>
      <arglist>(Point&lt; T &gt; p)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>GetPoint2</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>a64f427ec2a5a7ad8edb9f4010941f072</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPoint2</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>aacbb408cac39b52cb9595cb96ac92049</anchor>
      <arglist>(Point&lt; T &gt; p)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetLength</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>a069c49e12e58c999a189d0bb0227d419</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDistanceToLine</name>
      <anchorfile>classstira_1_1common_1_1LineSegment.html</anchorfile>
      <anchor>aa5da392df4b0b1cecfeebf69990b71ec</anchor>
      <arglist>(Point&lt; T &gt; p, bool isSegment=false)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::LocalBinaryPattern</name>
    <filename>classstira_1_1filter_1_1LocalBinaryPattern.html</filename>
    <member kind="function">
      <type></type>
      <name>LocalBinaryPattern</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a92714909817d86cd305d7b4595126963</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LocalBinaryPattern</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a533b5b9f4bafb93aa0243c4b983514f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; bool &gt;</type>
      <name>RunVector</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>aab89726e0cf11b745459f75688f5869c</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>RunCode</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>ac7a9ff77df57f13dea86e8cc9caa4a54</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>histogram::FloatHistogram *</type>
      <name>RunHistogram</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>abcbe11338a8cfa1648e82b39b98729b6</anchor>
      <arglist>(int ID=0)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; common::Point&lt; double &gt; &gt;</type>
      <name>GetSamplePoints</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>adc2470da753d9cdac04c4a1ee25c37ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>SignComparison</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a3c59acf4881ce10ea598afb0ae84cf41</anchor>
      <arglist>(double a, double b, double threshold, bool myType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePointGLTP</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a52fe2c87953a20ec69d72c717511a852</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int x, int y, double threshold, bool myType)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeJensenShannonDivergenceBetweenImagePatches</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a7b783df5e1cfd19221ccf31606752198</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int frameNr, int xTop1, int yTop1, int xBottom1, int yBottom1, int xTop2, int yTop2, int xBottom2, int yBottom2)</arglist>
    </member>
    <member kind="function">
      <type>histogram::FloatHistogram</type>
      <name>ComputePointLBPSymHistogram</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a8bf2cc6bf5027650037daeaa6beb501e</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int frameNr, int topX, int topY, int bottomX, int bottomY, double threshold, bool myType)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; int &gt; *</type>
      <name>ComputeLBPSymImage</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a730455226c58b4644c8023f9b3c04a6d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double threshold, bool myType)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>ComputePointLBPSym</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>a9f6f4be2a32f8054efc66dd730550745</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int x, int y, double threshold, bool myType)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunClassic</name>
      <anchorfile>classstira_1_1filter_1_1LocalBinaryPattern.html</anchorfile>
      <anchor>af855a437b51d4ed82234770ec74f4f5c</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::LocalOrientation</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</filename>
    <member kind="function">
      <type></type>
      <name>LocalOrientation</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>a34c0f84936a4181ee8f04b7d935a01d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LocalOrientation</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>a1fe5b2a7e914e955d1fc8d171a87ede5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMagnitude</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>af6aed39ceac78ae04aecd0bbe9afcc39</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMagnitude</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>a171d6389ec61895e7e0175a000f3d80c</anchor>
      <arglist>(double myMagnitude)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAngle</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>a3c72003573ad60c8f46b5951e1b6233f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAngle</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1LocalOrientation.html</anchorfile>
      <anchor>ae29d8cb3e4c45f8eee404384ab4a3338</anchor>
      <arglist>(double myAngle)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::LogGabor</name>
    <filename>classstira_1_1filter_1_1LogGabor.html</filename>
    <member kind="function">
      <type></type>
      <name>LogGabor</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a13e4784d8a207e50ea6162e0a2717bfa</anchor>
      <arglist>(Image *pImage)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~LogGabor</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>aa9d6ed8e1a726293516c73b4e6237a35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetCenterFrequency</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a5372a3e76c9630fe8ad873d3df120059</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCenterFrequency</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>abf22c7c3683badc47e7dace2d5a18bc2</anchor>
      <arglist>(double centerFrequency)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetRadialWidth</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a6d23eb83bc53d15377f16dc23eb0db91</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRadialWidth</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a363380b9d4dad55d0a51e4ca0ec46ed5</anchor>
      <arglist>(double radialWidth)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetCenterAngle</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>aa0f8e237f6051908d22cd89d346c3f83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetCenterAngle</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>aec4c08d6050b9fb62206c211f2d7a1ed</anchor>
      <arglist>(double centerAngle)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAngleSpread</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a155c43d820d10496cd44e881eccb5e3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAngleSpread</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a06244b7ef8c6b4872bfe4d780a7c9615</anchor>
      <arglist>(double angleSpread)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetRealResponse</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>ae562ee81d126199c3379da9089f5bb83</anchor>
      <arglist>(bool rescaleVisualize=true)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetImagResponse</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a51767237753a2e01af6a34f5e0aa888b</anchor>
      <arglist>(bool rescaleVisualize=true)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetTransferFunction</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a3f0072bf1951dd1025bc0c730559dfdf</anchor>
      <arglist>(bool rescaleVisualize=true)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GetMagnitude</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a07735ba2228397b98877d1e8bd4ff03a</anchor>
      <arglist>(bool rescaleVisualize=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>a1f7b51873e20fc3c26596b863b79c2b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1LogGabor.html</anchorfile>
      <anchor>ac34149289c964909ec46c705110ebad4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::imagedata::color::lut_entry_t</name>
    <filename>structstira_1_1imagedata_1_1color_1_1lut__entry__t.html</filename>
    <member kind="variable">
      <type>lab_t</type>
      <name>lab</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lut__entry__t.html</anchorfile>
      <anchor>a311bb09a6efccea75db9a41292d32a5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>cmyk_t</type>
      <name>cmyk</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lut__entry__t.html</anchorfile>
      <anchor>afe7961dc4bf2352c6bd9fb40d29e3373</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>structstira_1_1imagedata_1_1color_1_1lut__entry__t.html</anchorfile>
      <anchor>a6d7874311d43474b83a119c48aac5e8d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::MathUtils</name>
    <filename>classstira_1_1common_1_1MathUtils.html</filename>
    <member kind="function">
      <type></type>
      <name>MathUtils</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>abbda6c2600d3d51fcbdf4fdbbb6720b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MathUtils</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>afbc60582f04bbb1483a2392a91309326</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SolveQuadraticEquation</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a33903320715bc8f85049118ae6f97f3e</anchor>
      <arglist>(double a, double b, double c, double &amp;outSolution1, double &amp;outSolution2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SwitchValues</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a32008e477f585a177ecaee0dcd753853</anchor>
      <arglist>(double &amp;a, double &amp;b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SwitchValues</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a395bb3688da6f48aaa5e535df23de48b</anchor>
      <arglist>(int &amp;a, int &amp;b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetMin</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>af4ea26af4687605c4b07fc0f9f3da031</anchor>
      <arglist>(double value1, double value2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetMax</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a743284101d66293bda94ed8b288523e6</anchor>
      <arglist>(double value1, double value2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>CompareDoubles</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a85abee7d0f85dc475148fe9ff8f27b3a</anchor>
      <arglist>(const void *a, const void *b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>CompareFloats</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>aa6a69a338a44d7d91245975c32669b7a</anchor>
      <arglist>(const void *a, const void *b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>CompareIntegers</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a7a38ff74514e0e76f677b6fea40943d3</anchor>
      <arglist>(const void *a, const void *b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>ClipValue</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a1d14194470822da692c26c0c9734695b</anchor>
      <arglist>(int value, int min=0, int max=255)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ClipValue</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a95e981060b69736cb8680c7f8051b601</anchor>
      <arglist>(double value, double min=0.0, double max=255.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsBetween</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a5145cda4ac94a81b286f5b545ac28b23</anchor>
      <arglist>(double testValue, double underLimit, double upperLimit)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ApplyModulo</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ad497f57aeaf7fe3da7ffdf883f3bd177</anchor>
      <arglist>(double input, double modulo)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>PrintBitsInInt</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ac896a30799730b0d3fbc5328a5bafccc</anchor>
      <arglist>(unsigned int i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>PrintBitsInChar</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>aa63a021b21903cc5684945b5920b1197</anchor>
      <arglist>(unsigned char c)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned int</type>
      <name>CombineCharsInInt</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ae1d0c8bd45fbe0f9c365b2360d16e764</anchor>
      <arglist>(unsigned char i0, unsigned char i1, unsigned char i2, unsigned char i3)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; unsigned char &gt;</type>
      <name>SplitIntInChars</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ac0bc1721fc2c67ae9c9fa15cd7f40bbd</anchor>
      <arglist>(int value)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeArgument</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a83d0590dd9363d63a8eb7905703b8a57</anchor>
      <arglist>(double x, double y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ToRadians</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a51ab7a226260abec7aabd06b5c26eb9d</anchor>
      <arglist>(double degrees)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ToDegrees</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a76912556b8eeb8a2e20c3b594ae10d1a</anchor>
      <arglist>(double radians)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SolveLinearEquation</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>abc31bdf3f4eecbdeb59b0f3e8d088e27</anchor>
      <arglist>(double a, double b, double &amp;solution)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SolveQuadraticEquation</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>af0741f311e8292e9ff39b9649866cf83</anchor>
      <arglist>(std::complex&lt; double &gt; a, std::complex&lt; double &gt; b, std::complex&lt; double &gt; c, std::complex&lt; double &gt; &amp;outSolution1, std::complex&lt; double &gt; &amp;outSolution2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>LinearInterpolate</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a73b4b34ffbd11d7d89e4b0ca27486f50</anchor>
      <arglist>(double x0, double y0, double x1, double y1, double x)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputePSNR</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a3a6bbc5d74ee6aebfeb1b14cd917f273</anchor>
      <arglist>(double MSE, double peakValue=255.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GammaCorrect</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ace6ce636828514e9c3cdc7336affd028</anchor>
      <arglist>(double inValue, double gamma, double rangeMin=0.0, double rangeMax=255.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetSteerableInterPolationCoefficient</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ae88f80e6ee638928fcb2d65b8db0ca02</anchor>
      <arglist>(int i, int K, double theta)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Factorial</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a18be5e1e91c472cb2ccf6949e7160f23</anchor>
      <arglist>(const double &amp;inputNumber)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>ComputeIntegerPower</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a3744bb28d35e6fac7e45339da2ea314f</anchor>
      <arglist>(int myNumber, int myExponent)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; double &gt;</type>
      <name>GenerateGaussianSamples</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ae2d7188881d4630564eed2764d7f7cd8</anchor>
      <arglist>(double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; double &gt; &gt;</type>
      <name>GenerateGaussianPoints</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>af377d1e3ef1823df4480602f3e39dde2</anchor>
      <arglist>(int gaussCenterX, double sigma, bool scaleAmplitude=false, double amplitude=1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; Point&lt; double &gt; &gt;</type>
      <name>GenerateGaussianPoints</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a0e5c0368b962ef51dd6f52e0b1cc2c4c</anchor>
      <arglist>(std::vector&lt; Point&lt; double &gt; &gt; inPoints, int gaussCenterX, double sigma, bool scaleAmplitude, double amplitude)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Gaussian</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ade0ca08fd5b31a599f3eb9ba4515a974</anchor>
      <arglist>(double x, double mu, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Gaussian</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a6c15707b6be6bc51443a6c1859cf26a5</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianFirstDerivativeX1D</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a720e31c3794012e0fc85713156a53c2b</anchor>
      <arglist>(double x, double mu, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianSecondDerivateX1D</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a8977a4dcf5bf36abbfe347445f9daeca</anchor>
      <arglist>(double x, double mu, double sigma)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianDx</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a886f98ff905fb9e888f4daf548297334</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianDy</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>af335fcd475fc715957897d81b6c7ccbc</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianSecondDerivateX1D</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>abe701c13a191b1486cd4c07e4be915a3</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianD2y</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a5f0a477dba1791da9bacc3736b373ae5</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GaussianDxDy</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a660974dda6ff7fedffb65bd79c629d8a</anchor>
      <arglist>(double x, double y, double muX, double muY, double sigmaX, double sigmaY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>ComputeCrossCorrelation</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>a982200f53a2d81e5a35cbbfbdade0030</anchor>
      <arglist>(double *x, double *y, int nrSamples, int maxDelay)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>NormalizeVector</name>
      <anchorfile>classstira_1_1common_1_1MathUtils.html</anchorfile>
      <anchor>ae8358e9751c26cd713de7b6d0e76951d</anchor>
      <arglist>(std::vector&lt; double &gt; &amp;inVector)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::MedianFilter</name>
    <filename>classstira_1_1filter_1_1MedianFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>MedianFilter</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>af4f15fde50a9b08d0e8ef9409ff26687</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~MedianFilter</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>ad3afeda2492a105bb547a189f5ceecc1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunMedian</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>aac92906003a4e74268744346009352fa</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>RunMedian</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>a20d4f726c91a67b3fc0e8409489eb609</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGridIn, int size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunHybridMedian</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>a4b521447860df05199f81f3a6d2b472c</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunMedian</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>aa6130b6f7743b904901b15060d5657f7</anchor>
      <arglist>(Image *pImageIn, int size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunHybridMedian</name>
      <anchorfile>classstira_1_1filter_1_1MedianFilter.html</anchorfile>
      <anchor>a387ab899c19d8d40cd8b72426441b1de</anchor>
      <arglist>(Image *pImageIn, int size)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::MonotonicCubicSplineInterpolator</name>
    <filename>classstira_1_1common_1_1MonotonicCubicSplineInterpolator.html</filename>
    <member kind="function">
      <type></type>
      <name>MonotonicCubicSplineInterpolator</name>
      <anchorfile>classstira_1_1common_1_1MonotonicCubicSplineInterpolator.html</anchorfile>
      <anchor>a0fe596dd1edf58b5d03e6fdf4bd1b41c</anchor>
      <arglist>(std::vector&lt; std::pair&lt; double, double &gt; &gt; dataPoints)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Interpolate</name>
      <anchorfile>classstira_1_1common_1_1MonotonicCubicSplineInterpolator.html</anchorfile>
      <anchor>aebde2aee1e120d26c69c8aecba92ae49</anchor>
      <arglist>(double x)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::mycomparison</name>
    <filename>classstira_1_1imageanalysis_1_1mycomparison.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>mycomparison</name>
      <anchorfile>classstira_1_1imageanalysis_1_1mycomparison.html</anchorfile>
      <anchor>a49b8e3b3f65be656e7ba56a0f2c93219</anchor>
      <arglist>(const bool &amp;revparam=true)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>classstira_1_1imageanalysis_1_1mycomparison.html</anchorfile>
      <anchor>ad1ffd96889d00a423a6496b9ead74483</anchor>
      <arglist>(PixelElement&lt; T &gt; &amp;lhs, PixelElement&lt; T &gt; &amp;rhs) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::image::myMinMax</name>
    <filename>structstira_1_1image_1_1myMinMax.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::image::NearestNeighborInterpolator</name>
    <filename>classstira_1_1image_1_1NearestNeighborInterpolator.html</filename>
    <base>stira::image::Interpolator</base>
    <member kind="function">
      <type></type>
      <name>NearestNeighborInterpolator</name>
      <anchorfile>classstira_1_1image_1_1NearestNeighborInterpolator.html</anchorfile>
      <anchor>a4d1bc5e7584951b7c0c6dc1380b1b1c5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NearestNeighborInterpolator</name>
      <anchorfile>classstira_1_1image_1_1NearestNeighborInterpolator.html</anchorfile>
      <anchor>a7c3d490a3f62498bcb60d36060fbfac4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1image_1_1NearestNeighborInterpolator.html</anchorfile>
      <anchor>ad978510a14ca956154dfed6b388c8898</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double x, double y)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::NeighborPointPair</name>
    <filename>structstira_1_1common_1_1NeighborPointPair.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::NoiseEstimator</name>
    <filename>classstira_1_1wavelet_1_1NoiseEstimator.html</filename>
    <member kind="function">
      <type></type>
      <name>NoiseEstimator</name>
      <anchorfile>classstira_1_1wavelet_1_1NoiseEstimator.html</anchorfile>
      <anchor>a9a5a86ceb7ce422fc1dac1b60fe39019</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NoiseEstimator</name>
      <anchorfile>classstira_1_1wavelet_1_1NoiseEstimator.html</anchorfile>
      <anchor>af34f5eef310566a299d0495cd6e331e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1wavelet_1_1NoiseEstimator.html</anchorfile>
      <anchor>a1a97a2fb08c4397b18e84d2930ead4ca</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::NonLocalMeansFilter</name>
    <filename>classstira_1_1filter_1_1NonLocalMeansFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>NonLocalMeansFilter</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>a0a3185bd606c62997fad23328802be0a</anchor>
      <arglist>(int size=7)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NonLocalMeansFilter</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>a211eb783698a69aef4e05038faf45aae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBlockSize</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>a023c6d38d0b1f932eb1832ffe467c3e3</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBlockSize</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>ac6faccdda39c936654c4685762e682c5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigma</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>afd144c2cfe2beb3649bdd06770964d11</anchor>
      <arglist>(double sigma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigma</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>adf8515cc815d48b35e46538795d5c042</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1NonLocalMeansFilter.html</anchorfile>
      <anchor>ab5513eab6c2302abff7ce22edcaeab35</anchor>
      <arglist>(Image *pImageIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::NonSeparableFilter</name>
    <filename>classstira_1_1filter_1_1NonSeparableFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>NonSeparableFilter</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a830165d41f84e3f6b44f4124fc4bd717</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NonSeparableFilter</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a8b191c899ce9220f47165cb3a1afc0ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a67965640e55bcff454ffaef7e324cbf7</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput, double *filterKernel, int filterWidth, int filterHeight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunSobelX</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a3cbbb49aa2cc8d9e21c854805427bc4d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunSobelY</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>af55fd681312bb1dd57273da98d334567</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunSobelX</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a0ceec5b48e33746ebf7c516ddec4144f</anchor>
      <arglist>(Image *pInput)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunSobelY</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a0dbd29b89d6545dd782b3dbce4237ba0</anchor>
      <arglist>(Image *pInput)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static OrientationGrid *</type>
      <name>DetermineLocalMagnitudeAndOrientation</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>a4676048e6f25b3c2238d2cbe054c061f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetSobelXKernel</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>ac1e27ea09774a3cacf2206f0a8d130e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>GetSobelYKernel</name>
      <anchorfile>classstira_1_1filter_1_1NonSeparableFilter.html</anchorfile>
      <anchor>af9bf0964c6ea35096c92550e645134de</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::NonSubsampledTransform</name>
    <filename>classstira_1_1wavelet_1_1NonSubsampledTransform.html</filename>
    <base>stira::wavelet::Wavelet</base>
    <member kind="function">
      <type></type>
      <name>NonSubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1NonSubsampledTransform.html</anchorfile>
      <anchor>a34cd773fd7e5b58c641fd5975b2c8c66</anchor>
      <arglist>(WaveletType type=DAUBECHIES_2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~NonSubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1NonSubsampledTransform.html</anchorfile>
      <anchor>a4dd5f64e29b90f25b25a551cd3f55d63</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1wavelet_1_1NonSubsampledTransform.html</anchorfile>
      <anchor>aa560456aa224df3db2cc4705db45f6be</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceGrid, int nrScales)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1wavelet_1_1NonSubsampledTransform.html</anchorfile>
      <anchor>a5449ebcd48a453c3cd36188e207f3887</anchor>
      <arglist>(double threshold=0.0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::NumberGridTools</name>
    <filename>classstira_1_1image_1_1NumberGridTools.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>NumberGridTools</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>aa75df0e0a48229d98c770d59924b69f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~NumberGridTools</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a422f61d9ac7e01253d8405b577f65f69</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>CopyValues</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a7642278e6cd1564caaae5ed31c7fead9</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pSourceGrid, ArrayGrid&lt; T &gt; *pDestinationGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::IntensityPoint &gt;</type>
      <name>ProjectGridOnX</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a907fc768b25a54ca5bf5688d7beaae35</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::IntensityPoint &gt;</type>
      <name>ProjectGridOnX</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a20307fe37d4eef7ce04e53dbc9a51857</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::IntensityPoint &gt;</type>
      <name>ProjectGridOnY</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a072c0eae7c14a72c1f7d6975f71ae22a</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; common::IntensityPoint &gt;</type>
      <name>ProjectGridOnY</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a3549739670a70ffcf92743ef1c7904ff</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int xTopLeft, int yTopLeft, int xBottomRight, int yBottomRight)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputeLocalAutoCorrelation</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a2be72e6f6a96cf3505d7eba382d8a1b2</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int xCenter, int yCenter, int halfWindowSize)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalSquaredDifference</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a8d50816cc6a69696c1d755c6deb0dc3e</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1, ArrayGrid&lt; double &gt; *pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalCrossCorrelation</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a248c5eccca86600cbff4e508e67593cd</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1, ArrayGrid&lt; double &gt; *pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLocalMutualInformation</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>aa97fd81bef63e6ecbf7f210fdb7f8e00</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, int xTop1, int yTop1, int xBottom1, int yBottom1, ArrayGrid&lt; double &gt; *pGrid2, int xTop2, int yTop2, int xBottom2, int yBottom2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>CreateSquaredErrorGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>abcbf0f77a18ee9e7d41942a784137d2b</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, bool printOutput=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeMSE</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a8f9ecb12271212e3b90685f6e8c04448</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeMSEinROI</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a3206db28b06e6cb512d0801ca263c1c4</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputePSNR</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a25ff7096723a75766ab3798f59b77ec1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputePSNRinROI</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a000d889dc8fed8c0e4a671fbe261c3db</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputeSSIM</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a7729293c99dab77ed75ef077a1f061f3</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, int localWindowSize, double intensityRange=255.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputeSSIMinROI</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>aa2edf6e25b7731ed2e787bc6fe302c6d</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, int localWindowSize, double intensityRange=255.0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputePearsonCorrelation</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a75179e22a9abff6c5c9b05e84a4f4482</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ComputeMandersOverlap</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a619811e81c6cf903f62fc240286b17b2</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid1, ArrayGrid&lt; double &gt; *pGrid2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>CreateIntGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a4c66e07e239c463e2a577e296e4cf8fb</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>CreateDoubleGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a95245b2ee9e03e03f93e11e09de92bac</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>CreateDoubleGridFromComplexGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ac7b2055c3564770ac5295cdbc78a16c4</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>NegateGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ab7263bd05d136336341679d136e4a328</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>NegateGrid</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>aabfc781e5160309d69bdf4684aa85ad1</anchor>
      <arglist>(ArrayGrid&lt; int &gt; *pGrid, int maxValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetFirstDerivativeX</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ae973c773d726280ca4d105a8ab7d6b05</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetFirstDerivativeY</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a77726cd33ef4227625a4dd0dc8efef4a</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetSecondDerivativeXX</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a235495e33f49540e88b87fd77139f8c3</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetSecondDerivativeXY</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a995da236acd80d325923070fcf5f1e46</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T</type>
      <name>GetSecondDerivativeYY</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ab060b31b51e964aad09de5f2c7f6143b</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, int x, int y)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Rotate90DegreesClockwise</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ab25e77e676adb88f06b1db3108034a34</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Rotate90DegreesCounterClockwise</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a293b78050843fc7295f297abb90931a0</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>Rotate180Degrees</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a8811e5f369355af5f135eebe355a44f8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>LogPolarTransform</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>aa5c91e6fc16f4879bfbae7c7a470941e</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ClipValues</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a40377108c2e7eece715c502c564e10f4</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGrid, T desiredMin, T desiredMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>HardThreshold</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ad1c6b0711b1267ea27f1ea6389a86c0b</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double threshold)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; bool &gt; *</type>
      <name>BinaryThreshold</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a00d87f19005a1ef948d8a294f70e5d5f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, double threshold, bool thresholdAbsoluteValue=false)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; int &gt; *</type>
      <name>BinaryThresholdInteger</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>a08b837376a3e7cac5346c320421d80b4</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int threshold)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; T &gt; *</type>
      <name>AverageGrids</name>
      <anchorfile>classstira_1_1image_1_1NumberGridTools.html</anchorfile>
      <anchor>ab53eea598404edf7dc462cfb057855bf</anchor>
      <arglist>(std::vector&lt; ArrayGrid&lt; T &gt; * &gt; gridVector)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::OrientationGrid</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ColorExportMode</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a21c3d85c1dee56c4fb1d581c677eee84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXPORT_RGB_MODE</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a21c3d85c1dee56c4fb1d581c677eee84a432a0161af1ec5ddedd6533063483ed4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXPORT_HSV_MODE</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a21c3d85c1dee56c4fb1d581c677eee84ad545bea51d3e467afe5730581c794338</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXPORT_RGB_MODE</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a21c3d85c1dee56c4fb1d581c677eee84a432a0161af1ec5ddedd6533063483ed4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>EXPORT_HSV_MODE</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a21c3d85c1dee56c4fb1d581c677eee84ad545bea51d3e467afe5730581c794338</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>OrientationGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>af81eba88dbe1003215e299f8de13888c</anchor>
      <arglist>(int width, int height)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~OrientationGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a20b7e95025bcbfbca2bf43c0e5cb0d7c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>add3f67ce71342ec44e837a3e4c0039c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a58b12a73cd17b3f3fa2a66e1d691221c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetAngle</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a7a66974a27c25bbb60a3474d9f0e5142</anchor>
      <arglist>(int x, int y, double myAngle)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAngle</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>ad6d1b4d4ced29d61713e49421ad45798</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetOrientation</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a38e0249a6f417510aaf8a8f0a661a686</anchor>
      <arglist>(int x, int y, LocalOrientation *pLocalOrientation)</arglist>
    </member>
    <member kind="function">
      <type>LocalOrientation *</type>
      <name>GetOrientation</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a688150f093e74508a15ad368352f3a66</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMagnitude</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a26cd04e4f51a6f19910a6dbd4df40012</anchor>
      <arglist>(int x, int y, double myMagnitude)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMagnitude</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>ab87e379c37065b8be79a237cef5983f7</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; LocalOrientation &gt;</type>
      <name>GetOrientationVector</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>aa4796eadb30b304bf1ab30066e065a5b</anchor>
      <arglist>(int xMin, int yMin, int xMax, int yMax)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetMinMaxMagnitude</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>ab32559c65e3246d801e30af73893ad5b</anchor>
      <arglist>(double &amp;mmin, double &amp;mmax)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractMagnitudeGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a7579bc5ac3d4b7b72d9d2538f12891dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>VisualizeMagnitudeImage</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>ac2467cd200fc7e5d3937be7507657892</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractOrientationGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>a1078b851c0dfe6cdfdf83d9a2811fa2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>VisualizeOrientationImage</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1OrientationGrid.html</anchorfile>
      <anchor>ad8f29e59e23571f87d052a030b642521</anchor>
      <arglist>(double threshold, ColorExportMode myMode=EXPORT_HSV_MODE)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::PcaResult</name>
    <filename>structstira_1_1common_1_1PcaResult.html</filename>
    <member kind="variable">
      <type>Point&lt; double &gt;</type>
      <name>center</name>
      <anchorfile>structstira_1_1common_1_1PcaResult.html</anchorfile>
      <anchor>af1fe34a64f4fab020487ebd1db3c9d6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Point&lt; double &gt; &gt;</type>
      <name>vector</name>
      <anchorfile>structstira_1_1common_1_1PcaResult.html</anchorfile>
      <anchor>a2b181d8471bd29062f463b9c60d47a5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; double &gt;</type>
      <name>eigenValue</name>
      <anchorfile>structstira_1_1common_1_1PcaResult.html</anchorfile>
      <anchor>ae3f62adf4091a5fdb51733121373c526</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::PerlinNoise</name>
    <filename>classstira_1_1image_1_1PerlinNoise.html</filename>
    <member kind="function">
      <type></type>
      <name>PerlinNoise</name>
      <anchorfile>classstira_1_1image_1_1PerlinNoise.html</anchorfile>
      <anchor>a0f0e0d3a6a3246d676cbaf4d72c1f0c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PerlinNoise</name>
      <anchorfile>classstira_1_1image_1_1PerlinNoise.html</anchorfile>
      <anchor>a7d0ed806f2d1490946b02e2d347d551b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Generate</name>
      <anchorfile>classstira_1_1image_1_1PerlinNoise.html</anchorfile>
      <anchor>ab32333f31061cce248eb82a4da2ac9f8</anchor>
      <arglist>(float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GenerateNormalized</name>
      <anchorfile>classstira_1_1image_1_1PerlinNoise.html</anchorfile>
      <anchor>ae28b66d188834720e0206db379bacacb</anchor>
      <arglist>(float persistence, int octaves, unsigned int width, unsigned int height, float red, float green, float blue, int seed, float zoom)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::imageanalysis::PixelElement</name>
    <filename>structstira_1_1imageanalysis_1_1PixelElement.html</filename>
    <templarg>T</templarg>
    <member kind="variable">
      <type>T</type>
      <name>value</name>
      <anchorfile>structstira_1_1imageanalysis_1_1PixelElement.html</anchorfile>
      <anchor>a2716155cc2c00f3ffb7036daed76d120</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>x</name>
      <anchorfile>structstira_1_1imageanalysis_1_1PixelElement.html</anchorfile>
      <anchor>a80bce21d77257d1a9c0a6686bf519e0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>y</name>
      <anchorfile>structstira_1_1imageanalysis_1_1PixelElement.html</anchorfile>
      <anchor>ac35277cb68ba02b81f4a133e25e0f9ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::Point</name>
    <filename>classstira_1_1common_1_1Point.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9a283f1f87c3a013a3eee821e4d7a61f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1584ddb4c22c60deb0ff9cf86e63ff0</anchor>
      <arglist>(T xNew, T yNew, coordinateMode mode=COORDINATES_CARTESIAN, pointType myType=TYPE_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a480bb178302377666b55b5720d5bc8a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetRadius</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3a6ab4ef66ccfbc8db0c8b792c1e76a2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>add0a1eebb75a568ed725bd37f97a5f57</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>pointType</type>
      <name>GetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3e7672a9a905871d86764765099dd250</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8a614ce5b6317c277329da75fc6d4193</anchor>
      <arglist>(pointType type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetXAndY</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac4d31632a2214c54e06767363b2f85b6</anchor>
      <arglist>(T xNew, T yNew)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRadiusAndTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8e54f4a2c316c51b9df0e0fd33e81ea6</anchor>
      <arglist>(T radius, T theta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDistance</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ab0646714b5fd73d469f6602f4d1bcfcf</anchor>
      <arglist>(Point other=Point&lt; T &gt;(0, 0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToPolar</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac2d0039a6d738068a05c5660ca49938f</anchor>
      <arglist>(T xCenter=0, T yCenter=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToCartesian</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3ddc6a256242163fa91ffc4812b896ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorOrigin</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a054adb794d875b67dff80c0380fd58ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorXaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac5f54801f1854ace0598dc15c75eebc6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorYaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a28bf41d9a695b2bf280528708ae8e646</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a13cea9990cb7c6def1b26b21a7b61e95</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9714ff1d1981e6ffdc8a024229f86aca</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>operator+</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a29fa5b51617fb0c92bf5e2d048b7b51b</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>operator-</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a16a832bb278f56d3af6ea8345267fd9a</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator*</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a53b3166c1c603e0c24bf8b58574219a4</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>operator^</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a678c81fcafc605d8ebf2a74e10571ab2</anchor>
      <arglist>(Point&lt; T &gt; otherPoint)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>x</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1628a3f644bcc7f1565ded071ba2fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>y</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ad4d53eb6eb9a91261d5dbe490f8a5a91</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Point&lt; double &gt;</name>
    <filename>classstira_1_1common_1_1Point.html</filename>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9a283f1f87c3a013a3eee821e4d7a61f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1584ddb4c22c60deb0ff9cf86e63ff0</anchor>
      <arglist>(doublexNew, doubleyNew, coordinateMode mode=COORDINATES_CARTESIAN, pointType myType=TYPE_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a480bb178302377666b55b5720d5bc8a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetRadius</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3a6ab4ef66ccfbc8db0c8b792c1e76a2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>add0a1eebb75a568ed725bd37f97a5f57</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>pointType</type>
      <name>GetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3e7672a9a905871d86764765099dd250</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8a614ce5b6317c277329da75fc6d4193</anchor>
      <arglist>(pointType type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetXAndY</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac4d31632a2214c54e06767363b2f85b6</anchor>
      <arglist>(doublexNew, doubleyNew)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRadiusAndTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8e54f4a2c316c51b9df0e0fd33e81ea6</anchor>
      <arglist>(doubleradius, doubletheta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDistance</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ab0646714b5fd73d469f6602f4d1bcfcf</anchor>
      <arglist>(Point other=Point&lt; double &gt;(0, 0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToPolar</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac2d0039a6d738068a05c5660ca49938f</anchor>
      <arglist>(doublexCenter=0, doubleyCenter=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToCartesian</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3ddc6a256242163fa91ffc4812b896ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorOrigin</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a054adb794d875b67dff80c0380fd58ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorXaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac5f54801f1854ace0598dc15c75eebc6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorYaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a28bf41d9a695b2bf280528708ae8e646</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a13cea9990cb7c6def1b26b21a7b61e95</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9714ff1d1981e6ffdc8a024229f86aca</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; double &gt;</type>
      <name>operator+</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a29fa5b51617fb0c92bf5e2d048b7b51b</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; double &gt;</type>
      <name>operator-</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a16a832bb278f56d3af6ea8345267fd9a</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator*</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a53b3166c1c603e0c24bf8b58574219a4</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator^</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a678c81fcafc605d8ebf2a74e10571ab2</anchor>
      <arglist>(Point&lt; double &gt; otherPoint)</arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>x</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1628a3f644bcc7f1565ded071ba2fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>y</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ad4d53eb6eb9a91261d5dbe490f8a5a91</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Point&lt; int &gt;</name>
    <filename>classstira_1_1common_1_1Point.html</filename>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9a283f1f87c3a013a3eee821e4d7a61f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1584ddb4c22c60deb0ff9cf86e63ff0</anchor>
      <arglist>(intxNew, intyNew, coordinateMode mode=COORDINATES_CARTESIAN, pointType myType=TYPE_DEFAULT)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Point</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a480bb178302377666b55b5720d5bc8a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetRadius</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3a6ab4ef66ccfbc8db0c8b792c1e76a2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>add0a1eebb75a568ed725bd37f97a5f57</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>pointType</type>
      <name>GetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3e7672a9a905871d86764765099dd250</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetType</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8a614ce5b6317c277329da75fc6d4193</anchor>
      <arglist>(pointType type)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetXAndY</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac4d31632a2214c54e06767363b2f85b6</anchor>
      <arglist>(intxNew, intyNew)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRadiusAndTheta</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a8e54f4a2c316c51b9df0e0fd33e81ea6</anchor>
      <arglist>(intradius, inttheta)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDistance</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ab0646714b5fd73d469f6602f4d1bcfcf</anchor>
      <arglist>(Point other=Point&lt; int &gt;(0, 0))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToPolar</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac2d0039a6d738068a05c5660ca49938f</anchor>
      <arglist>(intxCenter=0, intyCenter=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ToCartesian</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a3ddc6a256242163fa91ffc4812b896ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorOrigin</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a054adb794d875b67dff80c0380fd58ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorXaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac5f54801f1854ace0598dc15c75eebc6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>MirrorYaxis</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a28bf41d9a695b2bf280528708ae8e646</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a13cea9990cb7c6def1b26b21a7b61e95</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a9714ff1d1981e6ffdc8a024229f86aca</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>operator+</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a29fa5b51617fb0c92bf5e2d048b7b51b</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>operator-</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a16a832bb278f56d3af6ea8345267fd9a</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator*</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a53b3166c1c603e0c24bf8b58574219a4</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator^</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>a678c81fcafc605d8ebf2a74e10571ab2</anchor>
      <arglist>(Point&lt; int &gt; otherPoint)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>x</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ac1628a3f644bcc7f1565ded071ba2fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>y</name>
      <anchorfile>classstira_1_1common_1_1Point.html</anchorfile>
      <anchor>ad4d53eb6eb9a91261d5dbe490f8a5a91</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::common::pointCluster</name>
    <filename>structstira_1_1common_1_1pointCluster.html</filename>
    <member kind="variable">
      <type>Point&lt; double &gt;</type>
      <name>center</name>
      <anchorfile>structstira_1_1common_1_1pointCluster.html</anchorfile>
      <anchor>a726654cb865be640d183c1c9d128c3fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Point&lt; double &gt; &gt;</type>
      <name>members</name>
      <anchorfile>structstira_1_1common_1_1pointCluster.html</anchorfile>
      <anchor>aedbee0bbe6e07b334d0096a549886581</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::common::Polygon</name>
    <filename>classstira_1_1common_1_1Polygon.html</filename>
    <member kind="function">
      <type></type>
      <name>Polygon</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>ab82d5b53326a3a6b3bce58a5f03c2811</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddVertex</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>a1399d23140330e785c236b459ab4dd98</anchor>
      <arglist>(Point&lt; double &gt; newVertex)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>GetNumberOfVertices</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>a3133e9b2c3ed31c22301a496c25294a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; double &gt;</type>
      <name>GetVertex</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>a78edd830841dc42cbfecf687527e8185</anchor>
      <arglist>(int nr)</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetVertexInt</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>ac9d785027802105fd52dee1cd1679e01</anchor>
      <arglist>(int nr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ChangeVertex</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>a42b1fd61c3ab8fad08c98d069fd66352</anchor>
      <arglist>(int nr, double x, double y)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsPointInPolygon</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>a513ff2fe284ceae9576b5cc5e31edb64</anchor>
      <arglist>(Point&lt; int &gt; testPoint)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetPolygonArea</name>
      <anchorfile>classstira_1_1common_1_1Polygon.html</anchorfile>
      <anchor>afa2d1f3dd0c9e61f4b5ff06977370f20</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::ProfileCorrect</name>
    <filename>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</filename>
    <member kind="function">
      <type></type>
      <name>ProfileCorrect</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>addeff7ba326615e09a7f8248e2465b65</anchor>
      <arglist>(ProfileData *pInputProfile, int nrGridPoints)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ProfileCorrect</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>a4afa898202650f6cb69ce3ba1acb78c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ProfileData *</type>
      <name>InterpolateSamplesToGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>a5ed7460ab727298c5153a42abc590c44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>FindInList</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>a463dc50c292aa97b7c47df5241cc68a2</anchor>
      <arglist>(vector&lt; lut_entry_t &gt; myTable, cmyk_t cmykEntry, lut_entry_t &amp;foundEntry)</arglist>
    </member>
    <member kind="function">
      <type>compare_neighbor_entry_t</type>
      <name>FindClosestGridPoint</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>a3f0f5fed4a04be12c49ec8005e74340d</anchor>
      <arglist>(vector&lt; lut_entry_t &gt; myTable, lab_t gridLabValue)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; compare_neighbor_entry_t &gt;</type>
      <name>FindNearestNeighbors</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileCorrect.html</anchorfile>
      <anchor>aa7ed144bca637d35bbb20cba44ef7493</anchor>
      <arglist>(vector&lt; lut_entry_t &gt; dataTable, lut_entry_t myEntry)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::ProfileData</name>
    <filename>classstira_1_1imagedata_1_1color_1_1ProfileData.html</filename>
    <member kind="function">
      <type></type>
      <name>ProfileData</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>adf30613b073d948cd29d7671ad5ad4c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~ProfileData</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>abf3b1b4b32b38583bd9b5b7035743517</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSizeA2B</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>af2cb653542e2f0901a584372d6971c5e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>lut_entry_t</type>
      <name>GetA2BEntry</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>ae68d2256c75152f22aa09402144da628</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>cmyk_t</type>
      <name>GetA2BEntryCmyk</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a1b62076ae0befa1aedbdfdeef0171ddd</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>lab_t</type>
      <name>GetA2BEntryLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a2e30ac12b4b2e89dda4863c8fa57c94c</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddA2BEntry</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a2759a358454cf20344b8580e31e239ab</anchor>
      <arglist>(lut_entry_t entry)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA2BEntryCmyk</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>aaebe0c3722da4ec2ed381f980b12ec35</anchor>
      <arglist>(int k, cmyk_t cmyk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetA2BEntryLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>abad31cd8eb8f1bb282f91fd8c121b397</anchor>
      <arglist>(int k, lab_t lab)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSizeB2A</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a1945239012b83ccfd347b7709dde98f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>lut_entry_t</type>
      <name>GetB2AEntry</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>ad2dd7abbbb695711ffb37b989ca8b3fb</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>cmyk_t</type>
      <name>GetB2AEntryCmyk</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>ae2e80ff7b45d913b6daaf18e35f298a0</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>lab_t</type>
      <name>GetB2AEntryLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a95a26ec02213e14a75f2379b6c54d1d6</anchor>
      <arglist>(int k)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddB2AEntry</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>aa1d8e2abd62be892466e243b3539be37</anchor>
      <arglist>(lut_entry_t entry)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetB2AEntryCmyk</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>ad447152566a6d75541c987b59ff317e2</anchor>
      <arglist>(int k, cmyk_t cmyk)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetB2AEntryLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a91cd3c70de825430b78c33c28870f422</anchor>
      <arglist>(int k, lab_t lab)</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; lut_entry_t &gt;</type>
      <name>A2B</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>a56c5410b74de9b5785d5e2bc596102e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; lut_entry_t &gt;</type>
      <name>B2A</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1ProfileData.html</anchorfile>
      <anchor>aedb2573e52d6b5dabaf3e6282ef14b07</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::Pyramid</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a04feacdb26abd423e31220df2afa42e1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceBand, int myNrScales, int myNrOrientations, bool isSubsampled, bool needsResidualLevels, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CreateBands</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2134ec9a41eab642ac759df5f7e7a950</anchor>
      <arglist>(int sourceWidth, int sourceHeight, bool isSubsampled=false, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1b89d89b3c5788f34bc57b15cd1bcea4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af62f13e5e624afc0b57058cf21d209a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac921c16bb6d014b67c2730fb58d4fe72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2b5c160205f5fcc15792fa8077994473</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4cecdc157828f385540cb756ae111521</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a93180c64176b12f2d2f53ca502967396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1cd9c6d89221ebe42c8f755a72e83a89</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a58f3370dfd770770f502d6aa8c470ef9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afa2c9d9f37344fec9af418e3dbca471c</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a120d1d9edae2c213da8b8fda7ee5832a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4334063904d5df048b8911dd3fbc1889</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; T &gt; *</type>
      <name>GetRecursiveScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a88d0dcb3ae6e02e1f2a50a53e344ba9e</anchor>
      <arglist>(int scale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2792437e94a8e0b4194a0ce05b898cf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFinestScaleNumber</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af1e64c9bec4011be47c6fa51d864422c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; T &gt; *</type>
      <name>GetResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af52bdece9c348277fb4ff7441a9347a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a22f0145965025f75c14d509b4e96656b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a39803b961692429d14f3ddab517b5fd8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; T &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a92ce7b5f464cda43d8738d138eb6befa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyValuesFrom</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac65ff9ffe6df8096ec7c2a1416b48b62</anchor>
      <arglist>(Pyramid&lt; T &gt; *pOtherPyramid)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetAverageConeRatioSubSampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a767a19b9fb95a89564a17eae8767a675</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetAverageConeRatioRedundant</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a021e4618919fba44ddf50a0959b64748</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsSubsampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afc0d2d41f9cb1783c0cd3a0d782b481c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>DownSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a8b31a28111e0f3ed0154c057d7b4a99b</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pBandIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>UpSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>aa5cee209960ac127dd8f3456bb20f8b1</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pBandIn, int upSampledWidth, int upSampledHeight)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; PyramidLevel&lt; T &gt; * &gt;</type>
      <name>mvpRecursivePyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a53ee3d5fbce89e91f56ab530ec51a499</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PyramidLevel&lt; T &gt; *</type>
      <name>mpResidualPyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a65d29e32c43daef27614aa475816ccb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpLowPassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a217c785e650854efb1ea1e6bf717468e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceDataGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a3469c21644208ca7add4e269f8bfc3bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5fc58007cd5e3cf08a08feea910ce468</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5debae576127028eb55e11620439646b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ae384c0d8f55ed41eddfc02ae0c0f4377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a9b1bd642af0f23bfec905c22522826cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a7bafc847c6e19d114b0b68351f50b58e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Pyramid&lt; double &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</filename>
    <member kind="function">
      <type></type>
      <name>Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a04feacdb26abd423e31220df2afa42e1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceBand, int myNrScales, int myNrOrientations, bool isSubsampled, bool needsResidualLevels, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CreateBands</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2134ec9a41eab642ac759df5f7e7a950</anchor>
      <arglist>(int sourceWidth, int sourceHeight, bool isSubsampled=false, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1b89d89b3c5788f34bc57b15cd1bcea4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af62f13e5e624afc0b57058cf21d209a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac921c16bb6d014b67c2730fb58d4fe72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2b5c160205f5fcc15792fa8077994473</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4cecdc157828f385540cb756ae111521</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a93180c64176b12f2d2f53ca502967396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1cd9c6d89221ebe42c8f755a72e83a89</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a58f3370dfd770770f502d6aa8c470ef9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afa2c9d9f37344fec9af418e3dbca471c</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a120d1d9edae2c213da8b8fda7ee5832a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4334063904d5df048b8911dd3fbc1889</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; double &gt; *</type>
      <name>GetRecursiveScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a88d0dcb3ae6e02e1f2a50a53e344ba9e</anchor>
      <arglist>(int scale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2792437e94a8e0b4194a0ce05b898cf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFinestScaleNumber</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af1e64c9bec4011be47c6fa51d864422c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; double &gt; *</type>
      <name>GetResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af52bdece9c348277fb4ff7441a9347a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a22f0145965025f75c14d509b4e96656b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a39803b961692429d14f3ddab517b5fd8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; double &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a92ce7b5f464cda43d8738d138eb6befa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyValuesFrom</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac65ff9ffe6df8096ec7c2a1416b48b62</anchor>
      <arglist>(Pyramid&lt; double &gt; *pOtherPyramid)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverageConeRatioSubSampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a767a19b9fb95a89564a17eae8767a675</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetAverageConeRatioRedundant</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a021e4618919fba44ddf50a0959b64748</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsSubsampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afc0d2d41f9cb1783c0cd3a0d782b481c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>DownSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a8b31a28111e0f3ed0154c057d7b4a99b</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBandIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>UpSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>aa5cee209960ac127dd8f3456bb20f8b1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBandIn, int upSampledWidth, int upSampledHeight)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; PyramidLevel&lt; double &gt; * &gt;</type>
      <name>mvpRecursivePyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a53ee3d5fbce89e91f56ab530ec51a499</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PyramidLevel&lt; double &gt; *</type>
      <name>mpResidualPyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a65d29e32c43daef27614aa475816ccb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpLowPassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a217c785e650854efb1ea1e6bf717468e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceDataGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a3469c21644208ca7add4e269f8bfc3bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5fc58007cd5e3cf08a08feea910ce468</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5debae576127028eb55e11620439646b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ae384c0d8f55ed41eddfc02ae0c0f4377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a9b1bd642af0f23bfec905c22522826cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a7bafc847c6e19d114b0b68351f50b58e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Pyramid&lt; std::complex&lt; double &gt; &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</filename>
    <member kind="function">
      <type></type>
      <name>Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a04feacdb26abd423e31220df2afa42e1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceBand, int myNrScales, int myNrOrientations, bool isSubsampled, bool needsResidualLevels, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>CreateBands</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2134ec9a41eab642ac759df5f7e7a950</anchor>
      <arglist>(int sourceWidth, int sourceHeight, bool isSubsampled=false, bool isFinestScaleSubsampled=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Pyramid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1b89d89b3c5788f34bc57b15cd1bcea4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af62f13e5e624afc0b57058cf21d209a6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac921c16bb6d014b67c2730fb58d4fe72</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2b5c160205f5fcc15792fa8077994473</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetSourceDataHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4cecdc157828f385540cb756ae111521</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a93180c64176b12f2d2f53ca502967396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a1cd9c6d89221ebe42c8f755a72e83a89</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a58f3370dfd770770f502d6aa8c470ef9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afa2c9d9f37344fec9af418e3dbca471c</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a120d1d9edae2c213da8b8fda7ee5832a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a4334063904d5df048b8911dd3fbc1889</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetRecursiveScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a88d0dcb3ae6e02e1f2a50a53e344ba9e</anchor>
      <arglist>(int scale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>HasResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a2792437e94a8e0b4194a0ce05b898cf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetFinestScaleNumber</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af1e64c9bec4011be47c6fa51d864422c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetResidualScale</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>af52bdece9c348277fb4ff7441a9347a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a22f0145965025f75c14d509b4e96656b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLowpassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a39803b961692429d14f3ddab517b5fd8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid)</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a92ce7b5f464cda43d8738d138eb6befa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CopyValuesFrom</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ac65ff9ffe6df8096ec7c2a1416b48b62</anchor>
      <arglist>(Pyramid&lt; std::complex&lt; double &gt; &gt; *pOtherPyramid)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>GetAverageConeRatioSubSampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a767a19b9fb95a89564a17eae8767a675</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>std::complex&lt; double &gt;</type>
      <name>GetAverageConeRatioRedundant</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a021e4618919fba44ddf50a0959b64748</anchor>
      <arglist>(int x, int y, int orientationNr, int coarsestScale, int finestScale)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsSubsampled</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>afc0d2d41f9cb1783c0cd3a0d782b481c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>DownSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a8b31a28111e0f3ed0154c057d7b4a99b</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBandIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>UpSampleGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>aa5cee209960ac127dd8f3456bb20f8b1</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBandIn, int upSampledWidth, int upSampledHeight)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; PyramidLevel&lt; std::complex&lt; double &gt; &gt; * &gt;</type>
      <name>mvpRecursivePyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a53ee3d5fbce89e91f56ab530ec51a499</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>PyramidLevel&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>mpResidualPyramidLevels</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a65d29e32c43daef27614aa475816ccb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpLowPassResidual</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a217c785e650854efb1ea1e6bf717468e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceDataGrid</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a3469c21644208ca7add4e269f8bfc3bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5fc58007cd5e3cf08a08feea910ce468</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a5debae576127028eb55e11620439646b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>ae384c0d8f55ed41eddfc02ae0c0f4377</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a9b1bd642af0f23bfec905c22522826cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>mScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1Pyramid.html</anchorfile>
      <anchor>a7bafc847c6e19d114b0b68351f50b58e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::PyramidBurtAdelson</name>
    <filename>classstira_1_1steerable_1_1PyramidBurtAdelson.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidBurtAdelson</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidBurtAdelson.html</anchorfile>
      <anchor>a3e71319feb74ba07e6e253a5f4f287fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidBurtAdelson</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidBurtAdelson.html</anchorfile>
      <anchor>ac6e4094cfc946169c99bc32d8558afd6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidBurtAdelson.html</anchorfile>
      <anchor>a38310f96589aed3a3d0c455760b9ca4a</anchor>
      <arglist>(Image *pImage, int nrScales)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidBurtAdelson.html</anchorfile>
      <anchor>a88123025ac07d2a383cd873c7de35b83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; double &gt; *</type>
      <name>GetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidBurtAdelson.html</anchorfile>
      <anchor>a29adb717db2afa42a8da5280f6979cf6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::PyramidComplex</name>
    <filename>classstira_1_1steerable_1_1PyramidComplex.html</filename>
    <base>PyramidMaster&lt; std::complex&lt; double &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>PyramidComplex</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>ac5d95ec1e2ecb52f631202e4821c99ae</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int myNrScales, int myNrOrientations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidComplex</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>a3ba66f660c2786af8557600e0d16a393</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>a35c4de18a6cd9406116d6c83e1fb34c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>afc55b208fa7025aaaa78db29047c38f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>a78b5af927633daee311b12df8a0b6f05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>VisualizeComplexBandpass</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>a7b5b58a5fa5bc0885b23cf45cc97817b</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGrid, std::string bandType, int scaleNr, int orientationNr)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>VisualizeReconstructedBandpass</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidComplex.html</anchorfile>
      <anchor>a723f1a3cd532057afb6853156c49a580</anchor>
      <arglist>(fouriertools::FFTBand *pFftBandIn, std::string bandType, int scaleNr, int orientationNr)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::pyramidapplications::PyramidContrastEnhancer</name>
    <filename>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidContrastEnhancer</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a603725aaf233c36a6831910145df1453</anchor>
      <arglist>(double sigma)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidContrastEnhancer</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a5f8257897997f1b0ccb483d07df5a01b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>ae4792f1c75de79784f827aa5fc2e9d66</anchor>
      <arglist>(Image *pImage, int nrScales, int nrOrientations, bool applyWavelet=false)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RunPyramid</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a561b3557ada29d27242c82a6f97e2bf5</anchor>
      <arglist>(Pyramid&lt; double &gt; *pPyramid, bool applyWavelet=false)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>Run3Colors</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a75da91ca3ba3426bc0638824f93accb5</anchor>
      <arglist>(Image *pImage, int nrScales, int nrOrientations, bool applyWavelet=false)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigmaNoise</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>aadc1b5c11a87b58b8428aa1c04649209</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigmaNoise</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>aef01ce68e7ff67aa733b5817b54edc15</anchor>
      <arglist>(double sigma)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetNoiseThresholdFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a62e2784cef518b3cabfde16d9f36c254</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNoiseThresholdFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a68ef4f178ee6c71198e6d1715388a362</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetNoiseThreshold</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a54bbf71c9133c0fd514b0cbb50750232</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNoiseThreshold</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a8b1c5b0b45b89c0cb14a856e6b27ab62</anchor>
      <arglist>(double threshold)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetNonLinearityDegree</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>abf62e55914032916789b40d49fb5e514</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetNonLinearityDegree</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>af76a15cb52246234096cdabc5192adcd</anchor>
      <arglist>(double degree)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetUpperLimitAmplificationFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a1973da289f26baed0a600d7b3459ff0b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUpperLimitAmplificationFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a4f22f8a58f2b8286bc7174c50886705d</anchor>
      <arglist>(double limit)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetDynamicRangeCompressionFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a2fa8a33251f29aa12881e2fb834720cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDynamicRangeCompressionFactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a89d948cf5885d41b279d856605ba5e25</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetUpperLimitAmplification</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a3cb9bc13489f3d936c475bfa43028d33</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetUpperLimitAmplification</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a0aab3763e20221ee3e114a7bb4f1a9e4</anchor>
      <arglist>(double limit)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TestAmplificationfactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a0debb53c3b63c3bbb0962f2c24cdc967</anchor>
      <arglist>(std::string fileName, double myMin, double myMax, double stepSize)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidContrastEnhancer.html</anchorfile>
      <anchor>a04fc00e647bd8ae7dc6de922f681e619</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::pyramidapplications::PyramidDenoiser</name>
    <filename>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidDenoiser</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>ae0988ccef4b66c88eda78052d138cc80</anchor>
      <arglist>(Pyramid&lt; double &gt; *pPyramid, ShrinkageRule myRule, double sigma)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidDenoiser</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a73dbc31087f8a80982b1f41fc3f88467</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetSigmaNoise</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a2ccf2cdaf877a334d09f45735f3baaf6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetSigmaNoise</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a1d5e338d85518c86f9c64144595d4977</anchor>
      <arglist>(double sigmaNoise)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>afe80c21ef39f327795ae9ad031ccca1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a295290b4c771e54157c0003d2cb2dc5b</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a52563e7b491170627d22861a6d72ef38</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorResidualToRecursiveLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>adfbdc07706fab1b20f0116ed66ca8f86</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a2e425c26b8f634cabcb20cbdeb821a24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetScaleFactorRecursiveLevel</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>abc74973d19c94c7eaac85887ff28a770</anchor>
      <arglist>(double factor)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Run</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a9a25f36762dbdeca1124f36ecc4877b9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeBivariateShrinkagefactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>add08f95e90fb3d6adfd2e65a46754e1e</anchor>
      <arglist>(double w1, double w2, double sigmaSignal, double sigmaNoise)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeWienerShrinkagefactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a2b7c5e28bbff94f146aed3a3fbd81bff</anchor>
      <arglist>(double sigmaSignal, double sigmaNoise)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ComputeLaplacianShrinkagefactor</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>a3f9fd418b29441c65182b02904ad7f34</anchor>
      <arglist>(double w1, double sigmaSignal, double sigmaNoise)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>EstimateSigmaSignal</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidDenoiser.html</anchorfile>
      <anchor>ab65e08693b6cddeb80fe2d4e9b2aab72</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBand, int xCenter, int yCenter, double sigmaNoise, int windowSize)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::pyramidapplications::PyramidKeyPointDetector</name>
    <filename>classstira_1_1pyramidapplications_1_1PyramidKeyPointDetector.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidKeyPointDetector</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidKeyPointDetector.html</anchorfile>
      <anchor>aed1af8b22518bba514688785d10bc2ca</anchor>
      <arglist>(Pyramid&lt; std::complex&lt; double &gt; &gt; *pPyramid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidKeyPointDetector</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidKeyPointDetector.html</anchorfile>
      <anchor>ac9bbaa6550b8ac749d25f731afed8978</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Run</name>
      <anchorfile>classstira_1_1pyramidapplications_1_1PyramidKeyPointDetector.html</anchorfile>
      <anchor>aad910a35f522f0ddc1656ef23806e6af</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::datastructures::PyramidLevel</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acf217864190d52fd8f09439db83ed554</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>aa4d10d18f83d70a0cd16c3d3456eeab6</anchor>
      <arglist>(const PyramidLevel&lt; T &gt; &amp;otherLevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a2b6349dad9d57b0aa1a62ec8d4ac6516</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; T &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>adcd28f4b269b202e1136165994b4597e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a6e2e48f0deeeafe40440a198fc4ddf0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>GetOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a12f5bcb0ee0ca2344fa021c3f4d3ae82</anchor>
      <arglist>(int orientation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a299af59b4e57806825bf2e6970efa196</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a37c6b7bedaeaa24dd52bcded111b5566</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReplaceOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a06e4ead71782676247a9b96fcdbc7008</anchor>
      <arglist>(int orientationIndex, ArrayGrid&lt; T &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearThisLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a186faa02f3465243e08d098eac791809</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acbfec133af01fcd2ae7f2d57b43d5790</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a1b5928e35b4f149eecde04eef75ca471</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PyramidLevel&lt; double &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acf217864190d52fd8f09439db83ed554</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>aa4d10d18f83d70a0cd16c3d3456eeab6</anchor>
      <arglist>(const PyramidLevel&lt; double &gt; &amp;otherLevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a2b6349dad9d57b0aa1a62ec8d4ac6516</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; double &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>adcd28f4b269b202e1136165994b4597e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a6e2e48f0deeeafe40440a198fc4ddf0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a12f5bcb0ee0ca2344fa021c3f4d3ae82</anchor>
      <arglist>(int orientation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a299af59b4e57806825bf2e6970efa196</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a37c6b7bedaeaa24dd52bcded111b5566</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReplaceOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a06e4ead71782676247a9b96fcdbc7008</anchor>
      <arglist>(int orientationIndex, ArrayGrid&lt; double &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearThisLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a186faa02f3465243e08d098eac791809</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acbfec133af01fcd2ae7f2d57b43d5790</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a1b5928e35b4f149eecde04eef75ca471</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PyramidLevel&lt; std::complex&lt; double &gt; &gt;</name>
    <filename>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acf217864190d52fd8f09439db83ed554</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>aa4d10d18f83d70a0cd16c3d3456eeab6</anchor>
      <arglist>(const PyramidLevel&lt; std::complex&lt; double &gt; &gt; &amp;otherLevel)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a2b6349dad9d57b0aa1a62ec8d4ac6516</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PyramidLevel&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>adcd28f4b269b202e1136165994b4597e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a6e2e48f0deeeafe40440a198fc4ddf0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a12f5bcb0ee0ca2344fa021c3f4d3ae82</anchor>
      <arglist>(int orientation)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>AddOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a299af59b4e57806825bf2e6970efa196</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>RemoveOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a37c6b7bedaeaa24dd52bcded111b5566</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ReplaceOrientedBand</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a06e4ead71782676247a9b96fcdbc7008</anchor>
      <arglist>(int orientationIndex, ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pBand)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ClearThisLevel</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a186faa02f3465243e08d098eac791809</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>acbfec133af01fcd2ae7f2d57b43d5790</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1imagedata_1_1datastructures_1_1PyramidLevel.html</anchorfile>
      <anchor>a1b5928e35b4f149eecde04eef75ca471</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::PyramidMaster</name>
    <filename>classstira_1_1steerable_1_1PyramidMaster.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6e711924652dfea56447cc119aa738d9</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int myNrScales, int myNrOrientations)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5a695a980071c86c4fcc715d44cfd23b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a00c186e39a5d8967002315b32fb2a7e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3cbcfc8fa871ecd5b5924adac3dc5617</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a11414b03bc2d936ff40317b63a967e2d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>fouriertools::FFTBand *</type>
      <name>SumFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa94495e6f6dd42d50ddabfa665bed30b</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetCopyOfReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa7356fd2831f49b15aa49e8d8e8183ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; T &gt; *</type>
      <name>GetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a93adf815c72796ce7db3b44f973f6655</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a4b948992313c43b4932715a8f2a46d2c</anchor>
      <arglist>(Pyramid&lt; T &gt; *pPyramid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a094550f4d78533952639caa547b01037</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a9f5f96874b8458e7fe3d6182712f21ef</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5312e981dcfa8c683f5b42a15af71f5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>accfa9c6e958baf4b351c24bca31402aa</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a415d8bbd65e9b9a2632744060ecd7355</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; vpFFTBandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a7b17ef15d26b0756b4772b8a72919cec</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5659515f58538e61b6469a597e3df510</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a787d4cced6ba6feaf0a5cfd5cfc78067</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>MergeAndReconstructFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>af0ce3e89cbd77da986504b0c27540374</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ClearFFTVector</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a392d1d4cc7d3afd1c330b2c5e616bd2d</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; &amp;set)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa5a2d276578aee78457b043597b87104</anchor>
      <arglist>(fouriertools::FFTBand *pFFTBand)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>GetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8160a13bc28ad83bec3241e4191a413b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CleanFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be7a7a1eed02eb0d927d9f92c8dd2a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>ViewTransferFunction</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a405bab2184ceec320c5555d173fe2373</anchor>
      <arglist>(fouriertools::FFTBand *pTransferFunction, std::string token, int scale, int orientation, int maxNrOfOrientations, bool isForward)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pyramid&lt; T &gt; *</type>
      <name>mpPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a87c0313bdf7f17b28cb79e8b39426b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6084cfaab8d42621202330bade649f2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3f430498531dc91fbe47852ee3a54268</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>acb5a0ddbea76821d22dacc51ba118dda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5760bc20202e566282ad3129be0b29db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ad98f49b71e5a9d2d0ee2b0928f0b6ce2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a10dc28f7e639ee94b479a6f81a007aa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>mIsForwardTransform</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>afe013c50800c679b36b82d9727505ccf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpTmpHighpassGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac6299d3c729a8f0692c25be99a589754</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mDecompositionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be2d0a9c88d01f9c1ad533e29974921</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mReconstructionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac0cff0abb5610c600e71828aff7e9dcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>mpFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa56ed8860c0746df51012e387176ddf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentScale</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a119f453d7013c4b43ad2ae9a34f4853f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentOrientation</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>abe07fb6e1230a60e81ae90b500e8720c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PyramidMaster&lt; double &gt;</name>
    <filename>classstira_1_1steerable_1_1PyramidMaster.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6e711924652dfea56447cc119aa738d9</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int myNrScales, int myNrOrientations)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5a695a980071c86c4fcc715d44cfd23b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a00c186e39a5d8967002315b32fb2a7e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3cbcfc8fa871ecd5b5924adac3dc5617</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a11414b03bc2d936ff40317b63a967e2d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>fouriertools::FFTBand *</type>
      <name>SumFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa94495e6f6dd42d50ddabfa665bed30b</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetCopyOfReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa7356fd2831f49b15aa49e8d8e8183ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; double &gt; *</type>
      <name>GetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a93adf815c72796ce7db3b44f973f6655</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a4b948992313c43b4932715a8f2a46d2c</anchor>
      <arglist>(Pyramid&lt; double &gt; *pPyramid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a094550f4d78533952639caa547b01037</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a9f5f96874b8458e7fe3d6182712f21ef</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5312e981dcfa8c683f5b42a15af71f5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>accfa9c6e958baf4b351c24bca31402aa</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a415d8bbd65e9b9a2632744060ecd7355</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; vpFFTBandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a7b17ef15d26b0756b4772b8a72919cec</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5659515f58538e61b6469a597e3df510</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a787d4cced6ba6feaf0a5cfd5cfc78067</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>MergeAndReconstructFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>af0ce3e89cbd77da986504b0c27540374</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ClearFFTVector</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a392d1d4cc7d3afd1c330b2c5e616bd2d</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; &amp;set)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa5a2d276578aee78457b043597b87104</anchor>
      <arglist>(fouriertools::FFTBand *pFFTBand)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>GetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8160a13bc28ad83bec3241e4191a413b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CleanFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be7a7a1eed02eb0d927d9f92c8dd2a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>ViewTransferFunction</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a405bab2184ceec320c5555d173fe2373</anchor>
      <arglist>(fouriertools::FFTBand *pTransferFunction, std::string token, int scale, int orientation, int maxNrOfOrientations, bool isForward)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pyramid&lt; double &gt; *</type>
      <name>mpPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a87c0313bdf7f17b28cb79e8b39426b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6084cfaab8d42621202330bade649f2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3f430498531dc91fbe47852ee3a54268</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>acb5a0ddbea76821d22dacc51ba118dda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5760bc20202e566282ad3129be0b29db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ad98f49b71e5a9d2d0ee2b0928f0b6ce2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a10dc28f7e639ee94b479a6f81a007aa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>mIsForwardTransform</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>afe013c50800c679b36b82d9727505ccf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpTmpHighpassGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac6299d3c729a8f0692c25be99a589754</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mDecompositionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be2d0a9c88d01f9c1ad533e29974921</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mReconstructionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac0cff0abb5610c600e71828aff7e9dcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>mpFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa56ed8860c0746df51012e387176ddf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentScale</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a119f453d7013c4b43ad2ae9a34f4853f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentOrientation</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>abe07fb6e1230a60e81ae90b500e8720c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PyramidMaster&lt; std::complex&lt; double &gt; &gt;</name>
    <filename>classstira_1_1steerable_1_1PyramidMaster.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6e711924652dfea56447cc119aa738d9</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int myNrScales, int myNrOrientations)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PyramidMaster</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5a695a980071c86c4fcc715d44cfd23b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a00c186e39a5d8967002315b32fb2a7e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3cbcfc8fa871ecd5b5924adac3dc5617</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a11414b03bc2d936ff40317b63a967e2d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>fouriertools::FFTBand *</type>
      <name>SumFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa94495e6f6dd42d50ddabfa665bed30b</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetCopyOfReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa7356fd2831f49b15aa49e8d8e8183ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>GetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a93adf815c72796ce7db3b44f973f6655</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a4b948992313c43b4932715a8f2a46d2c</anchor>
      <arglist>(Pyramid&lt; std::complex&lt; double &gt; &gt; *pPyramid)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a094550f4d78533952639caa547b01037</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a9f5f96874b8458e7fe3d6182712f21ef</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>ExtractL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5312e981dcfa8c683f5b42a15af71f5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ExtractB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>accfa9c6e958baf4b351c24bca31402aa</anchor>
      <arglist>(common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a415d8bbd65e9b9a2632744060ecd7355</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; vpFFTBandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB0</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a7b17ef15d26b0756b4772b8a72919cec</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructL</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5659515f58538e61b6469a597e3df510</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>ReconstructB</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a787d4cced6ba6feaf0a5cfd5cfc78067</anchor>
      <arglist>(ArrayGrid&lt; std::complex&lt; double &gt; &gt; *pGridIn, common::NumberMode myMode)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>MergeAndReconstructFFTBands</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>af0ce3e89cbd77da986504b0c27540374</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; fftSubbandSet)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>ClearFFTVector</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a392d1d4cc7d3afd1c330b2c5e616bd2d</anchor>
      <arglist>(std::vector&lt; fouriertools::FFTBand * &gt; &amp;set)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa5a2d276578aee78457b043597b87104</anchor>
      <arglist>(fouriertools::FFTBand *pFFTBand)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>GetFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8160a13bc28ad83bec3241e4191a413b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>CleanFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be7a7a1eed02eb0d927d9f92c8dd2a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>ViewTransferFunction</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a405bab2184ceec320c5555d173fe2373</anchor>
      <arglist>(fouriertools::FFTBand *pTransferFunction, std::string token, int scale, int orientation, int maxNrOfOrientations, bool isForward)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pyramid&lt; std::complex&lt; double &gt; &gt; *</type>
      <name>mpPyramid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a87c0313bdf7f17b28cb79e8b39426b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a6084cfaab8d42621202330bade649f2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpReconstructedGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a3f430498531dc91fbe47852ee3a54268</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>acb5a0ddbea76821d22dacc51ba118dda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a5760bc20202e566282ad3129be0b29db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mWidth</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ad98f49b71e5a9d2d0ee2b0928f0b6ce2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mHeight</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a10dc28f7e639ee94b479a6f81a007aa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>mIsForwardTransform</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>afe013c50800c679b36b82d9727505ccf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpTmpHighpassGrid</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac6299d3c729a8f0692c25be99a589754</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mDecompositionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a8be2d0a9c88d01f9c1ad533e29974921</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::complex&lt; double &gt;</type>
      <name>mReconstructionFactor</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>ac0cff0abb5610c600e71828aff7e9dcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>fouriertools::FFTBand *</type>
      <name>mpFFTBand</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>aa56ed8860c0746df51012e387176ddf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentScale</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>a119f453d7013c4b43ad2ae9a34f4853f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentOrientation</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidMaster.html</anchorfile>
      <anchor>abe07fb6e1230a60e81ae90b500e8720c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::steerable::PyramidReal</name>
    <filename>classstira_1_1steerable_1_1PyramidReal.html</filename>
    <base>PyramidMaster&lt; double &gt;</base>
    <member kind="function">
      <type></type>
      <name>PyramidReal</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>a1da82ca06c4b29aecdfd4e3f6c7e53c8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, int myNrScales, int myNrOrientations)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidReal</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>aa3cbe8859297d33230c5bfc2941f08e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>af5a998a0e23e9ca114f1b29ddced4dd4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>a7a5bc94640e8bfae80d7f662b61ea56c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Diagnose</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>a93823874a29a9418e2cd09e1a7ef8333</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>VisualizeReconstructedBandpass</name>
      <anchorfile>classstira_1_1steerable_1_1PyramidReal.html</anchorfile>
      <anchor>a49cc4d5ebe0681ee5e5e21302d64cc26</anchor>
      <arglist>(fouriertools::FFTBand *pFftSubband, std::string bandType, int scaleNr, int orientationNr)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::PyramidTools</name>
    <filename>classstira_1_1image_1_1PyramidTools.html</filename>
    <member kind="function">
      <type></type>
      <name>PyramidTools</name>
      <anchorfile>classstira_1_1image_1_1PyramidTools.html</anchorfile>
      <anchor>a57910eca1fa036d768f485db65af44b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~PyramidTools</name>
      <anchorfile>classstira_1_1image_1_1PyramidTools.html</anchorfile>
      <anchor>a354cd43db61cd305d38585d27cef791b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>VisualizeRealPyramid</name>
      <anchorfile>classstira_1_1image_1_1PyramidTools.html</anchorfile>
      <anchor>a05d24febe3482abd886b616c6ec3106b</anchor>
      <arglist>(Pyramid&lt; double &gt; *pPyramid)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>qParam</name>
    <filename>structqParam.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::QuantileNormalDistribution</name>
    <filename>classstira_1_1common_1_1QuantileNormalDistribution.html</filename>
    <member kind="function">
      <type></type>
      <name>QuantileNormalDistribution</name>
      <anchorfile>classstira_1_1common_1_1QuantileNormalDistribution.html</anchorfile>
      <anchor>ae35f73e3cf94476be73b12f41f3d1624</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>Run</name>
      <anchorfile>classstira_1_1common_1_1QuantileNormalDistribution.html</anchorfile>
      <anchor>aff7645d6d4945a2983f7f1d427fa494b</anchor>
      <arglist>(double p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; double &gt;</type>
      <name>AnalyseNormalizedHistogram</name>
      <anchorfile>classstira_1_1common_1_1QuantileNormalDistribution.html</anchorfile>
      <anchor>aaadb764a3cd539859a0faf54a1992e1a</anchor>
      <arglist>(std::vector&lt; double &gt; normalizedHistogram, double &amp;rho, bool writeQuantiles=false)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Random</name>
    <filename>classRandom.html</filename>
    <class kind="struct">Random::dSquared</class>
  </compound>
  <compound kind="class">
    <name>stira::common::RectangularROI</name>
    <filename>classstira_1_1common_1_1RectangularROI.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a44ce5ad8ee8c5127e5297a4c7d2ab52c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a97e0e4c99ab65ce289ca394f0f818273</anchor>
      <arglist>(Point&lt; T &gt; topLeftCorner, Point&lt; T &gt; bottomRightCorner)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a777158e453b462ff0dad6032a334e1fd</anchor>
      <arglist>(T topLeftX, T topLeftY, T bottomRightX, T bottomRightY)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a5a893312ba548fbf25f9bf272348f0c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>GetTopLeftCorner</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>ac0779792a760de522c03ff277f754c17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>GetBottomRightCorner</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a6384bf40f547ebefd1b8b155deb61223</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; T &gt;</type>
      <name>GetCenter</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a82d27a2b21b3810ec253483a78ed02b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a08ac9ed616e2cf52a85d682b247391d1</anchor>
      <arglist>(Point&lt; T &gt; candidatePoint)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>ae9b04b138096465a9eba9a43b4b02afc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a6e381a854c4495cebfe2636214a016f1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RectangularROI&lt; int &gt;</name>
    <filename>classstira_1_1common_1_1RectangularROI.html</filename>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a44ce5ad8ee8c5127e5297a4c7d2ab52c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a97e0e4c99ab65ce289ca394f0f818273</anchor>
      <arglist>(Point&lt; int &gt; topLeftCorner, Point&lt; int &gt; bottomRightCorner)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a777158e453b462ff0dad6032a334e1fd</anchor>
      <arglist>(inttopLeftX, inttopLeftY, intbottomRightX, intbottomRightY)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~RectangularROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a5a893312ba548fbf25f9bf272348f0c8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetTopLeftCorner</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>ac0779792a760de522c03ff277f754c17</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetBottomRightCorner</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a6384bf40f547ebefd1b8b155deb61223</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Point&lt; int &gt;</type>
      <name>GetCenter</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a82d27a2b21b3810ec253483a78ed02b6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsInROI</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a08ac9ed616e2cf52a85d682b247391d1</anchor>
      <arglist>(Point&lt; int &gt; candidatePoint)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetWidth</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>ae9b04b138096465a9eba9a43b4b02afc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetHeight</name>
      <anchorfile>classstira_1_1common_1_1RectangularROI.html</anchorfile>
      <anchor>a6e381a854c4495cebfe2636214a016f1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RegistrationDemon</name>
    <filename>classRegistrationDemon.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::registration::RegistrationWrapper</name>
    <filename>classstira_1_1registration_1_1RegistrationWrapper.html</filename>
    <member kind="function">
      <type></type>
      <name>RegistrationWrapper</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a6302fa2e97f6943b9131322cfdfdee5f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pMasterGrid, ArrayGrid&lt; double &gt; *pSlaveGrid)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~RegistrationWrapper</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a4764a839331f253d009b8e74fbeb2ee2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a45b27baf6410dfe704099ccc1f796b77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetRegisteredGrid</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a9915241daabd5a6bb739dc78815b90b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>image::AffineTransform *</type>
      <name>GetResultingTransform</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a1ccf258bb717c44bd32c4c10d37742d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintTransform</name>
      <anchorfile>classstira_1_1registration_1_1RegistrationWrapper.html</anchorfile>
      <anchor>a8cc93893bcd9ac6757b7ce6eb1b1449f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::contrastenhance::Retinex</name>
    <filename>classstira_1_1contrastenhance_1_1Retinex.html</filename>
    <member kind="function">
      <type></type>
      <name>Retinex</name>
      <anchorfile>classstira_1_1contrastenhance_1_1Retinex.html</anchorfile>
      <anchor>a3530acb0f787e789e02e4c3a5f799121</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Retinex</name>
      <anchorfile>classstira_1_1contrastenhance_1_1Retinex.html</anchorfile>
      <anchor>a09f389dab67f3241ab317fd8f6431707</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunMSRCR</name>
      <anchorfile>classstira_1_1contrastenhance_1_1Retinex.html</anchorfile>
      <anchor>af3c076f321afbe8f6109515c32ef9496</anchor>
      <arglist>(Image *pSourceImage, double lowerFraction, double upperFraction, bool applyColorCorrection=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunMSR</name>
      <anchorfile>classstira_1_1contrastenhance_1_1Retinex.html</anchorfile>
      <anchor>ad3cb7f66cd94d8b4bedf0da6ede78d21</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInGrid, double lowerFraction, double upperFraction)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::RichardsonLucyDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</filename>
    <base>stira::deconvolve::IterativeDeconvolve</base>
    <member kind="function">
      <type></type>
      <name>RichardsonLucyDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a73ff7048b683d0032b4116c93d2781dc</anchor>
      <arglist>(Image *pDegradedImage, regularizationType myRegularizationType=REGULARIZE_NONE, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RichardsonLucyDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>ab62cd1a411733d201a7b44b5f45a4d33</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF, regularizationType myRegularizationType=REGULARIZE_NONE, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~RichardsonLucyDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a5b1cf61e3f7171d89f4e2ef3d3b3503f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>ac40013072d1e3317773289e25c7c06f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>regularizationType</type>
      <name>GetRegularizationType</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a72ce3d9073d5277aa18ede523263cef3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetRegularizationType</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>ad0b53f16b25117f032d70c4bd9a56b17</anchor>
      <arglist>(regularizationType myType)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEnforceIntensityRange</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a96f11ae4a5e6f86fdbaf64ebc932f154</anchor>
      <arglist>(bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetEnforceIntensityRange</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a10c8657dbbca2b76b72706e3b6ddb918</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1deconvolve_1_1RichardsonLucyDeconvolve.html</anchorfile>
      <anchor>a0cfba68ec52e2e36b46af462a937cd26</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::RigidTransform</name>
    <filename>classstira_1_1image_1_1RigidTransform.html</filename>
    <base>stira::image::GeometricTransform</base>
    <member kind="function">
      <type></type>
      <name>RigidTransform</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>a27182e9bb966c4daf8f2958091115216</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~RigidTransform</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>a0912d46cb72e36b53371fb0af0436eaf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetTheta</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>acece8d299160bfed97faebeeb7be777a</anchor>
      <arglist>(double theta)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaX</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>a8043047996a3290aae16823d6ec5ac20</anchor>
      <arglist>(double dx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaY</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>ad94150c0f229f63dc619aa98a4a81768</anchor>
      <arglist>(double dy)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>RotateAroundCenter</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>a488aefba6993e886ab64eef64def38ac</anchor>
      <arglist>(Image *pImageIn, double theta)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>RotateAroundCenter</name>
      <anchorfile>classstira_1_1image_1_1RigidTransform.html</anchorfile>
      <anchor>ad8c701b47479290707013bda07b7cd42</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double theta)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>rOper</name>
    <filename>structrOper.html</filename>
  </compound>
  <compound kind="struct">
    <name>rParam</name>
    <filename>structrParam.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::histogram::RunLengthHistogram</name>
    <filename>classstira_1_1histogram_1_1RunLengthHistogram.html</filename>
    <member kind="function">
      <type></type>
      <name>RunLengthHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>aa0c7fb3ffe6cb0eff1f11fe6e83a5666</anchor>
      <arglist>(int maxWidth, int maxLengthHistogram)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RunLengthHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>a419a10a1c175a747b7b2b79e63b5ae8f</anchor>
      <arglist>(const RunLengthHistogram &amp;runLengthHistogram)</arglist>
    </member>
    <member kind="function">
      <type>RunLengthHistogram *</type>
      <name>Clone</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>a4bda5871fc5d149280e482f5acf2f7c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Analyse</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>a68f1b5fe55f072976735ae9e48248ef4</anchor>
      <arglist>(std::vector&lt; int &gt; vYarnWidths, int startIndex=0)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; CurveSegment &gt;</type>
      <name>GetSegmentsWithWidth</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>a8107d71efaf52a6c2f2c46eb3cebebce</anchor>
      <arglist>(int width)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; CurveSegment &gt;</type>
      <name>GetSegmentsWithGivenWidthOfGivenLength</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>ac74fb6e1c374d792735425b115e560ac</anchor>
      <arglist>(int width, int length)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; CurveSegment &gt;</type>
      <name>GetLongestSegmentsWithGivenWidth</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>ae04f614b84f46af9bc3ff8a410aa4234</anchor>
      <arglist>(int width, unsigned int nrSegments)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>CountSegmentsWithGivenWidthOfGivenLength</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>a062a93df05e25d309fcac0db44df29e7</anchor>
      <arglist>(int width, int length)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>ComputeEntropy</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>abf91d7651a5345cc3d3e40578e19df93</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WriteSegments</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>af5b3f29fb24bea7bce9bbeffd4e2ce6c</anchor>
      <arglist>(std::string fileName, int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>WriteHistogram</name>
      <anchorfile>classstira_1_1histogram_1_1RunLengthHistogram.html</anchorfile>
      <anchor>ae6add995e22b9976ade92e4782833a0f</anchor>
      <arglist>(std::string fileName, int index)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::SeparableFilter</name>
    <filename>classstira_1_1filter_1_1SeparableFilter.html</filename>
    <member kind="function">
      <type></type>
      <name>SeparableFilter</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a7f003018274bf03f4ee711e825f0a1d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SeparableFilter</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a7bad6b9dbf50b34c55c31304c02053c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>RunRow</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a4dd84d18e8a2c0ff495daf0923909eb6</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput, ArrayGrid&lt; double &gt; *pOutput, double *filtx, int filterLengthX, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>RunColumn</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>ade6eda6394bd2c1b3ea1719a9e99d484</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInputBand, ArrayGrid&lt; double &gt; *pOutputBand, double *filty, int filterLengthY, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunRowColumn</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a2f0b8b0d1000c38dd60c00e68132db94</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunColumnRow</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a4b56165f3167d906fcd92af95317a11f</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunRowColumn</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a0a8a25a1870ce35980da27fb9595c6e0</anchor>
      <arglist>(Image *pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Image *</type>
      <name>RunColumnRow</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>ad08cc124abe255e1a1f0c90269fb9bbf</anchor>
      <arglist>(Image *pInput, double *filterTapX, double *filterTapY, int filterLengthX, int filterLengthY, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>BasicFilter1D</name>
      <anchorfile>classstira_1_1filter_1_1SeparableFilter.html</anchorfile>
      <anchor>a8b84db40822d65e912b751577a39cc7f</anchor>
      <arglist>(double *pInputArray1D, double *pFilterKernel, double *pOutputArray1D, int inputLength, int filterLength, GridExtender&lt; double &gt;::ExtensionType myType=GridExtender&lt; double &gt;::EXTEND_MIRROR)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::SimulateDegradation</name>
    <filename>classstira_1_1deconvolve_1_1SimulateDegradation.html</filename>
    <member kind="function">
      <type></type>
      <name>SimulateDegradation</name>
      <anchorfile>classstira_1_1deconvolve_1_1SimulateDegradation.html</anchorfile>
      <anchor>a114117116fb3568d512957a46b69f757</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SimulateDegradation</name>
      <anchorfile>classstira_1_1deconvolve_1_1SimulateDegradation.html</anchorfile>
      <anchor>a1d815b406d9f118f00cb0776f8f23c9b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::SLIC</name>
    <filename>classstira_1_1imageanalysis_1_1SLIC.html</filename>
    <member kind="function">
      <type>void</type>
      <name>DoSuperpixelSegmentation_ForGivenSuperpixelSize</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a4eb74fd10242246cf189fa4add599c54</anchor>
      <arglist>(const unsigned int *ubuff, const int width, const int height, int *&amp;klabels, int &amp;numlabels, const int &amp;superpixelsize, const double &amp;compactness)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a2f30c6ebc4752906083ecd8b030fd049</anchor>
      <arglist>(const unsigned int *ubuff, const int width, const int height, int *&amp;klabels, int &amp;numlabels, const int &amp;K, const double &amp;compactness)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DoSupervoxelSegmentation</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a9cfd63d101e45c12e3324a0ce60dd639</anchor>
      <arglist>(unsigned int **&amp;ubuffvec, const int &amp;width, const int &amp;height, const int &amp;depth, int **&amp;klabels, int &amp;numlabels, const int &amp;supervoxelsize, const double &amp;compactness)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SaveSuperpixelLabels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a9de56bcd1d4a78ebaefe84f44290e5ef</anchor>
      <arglist>(const int *&amp;labels, const int &amp;width, const int &amp;height, const string &amp;filename, const string &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SaveSupervoxelLabels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a9686a16058f162b34f1336564ea15b56</anchor>
      <arglist>(const int **&amp;labels, const int &amp;width, const int &amp;height, const int &amp;depth, const string &amp;filename, const string &amp;path)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>DrawContoursAroundSegments</name>
      <anchorfile>classstira_1_1imageanalysis_1_1SLIC.html</anchorfile>
      <anchor>a05959a482d07269f8470d0d1cc55d974</anchor>
      <arglist>(unsigned int *&amp;segmentedImage, int *&amp;labels, const int &amp;width, const int &amp;height, const unsigned int &amp;color)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::histogram::Spatiogram</name>
    <filename>classstira_1_1histogram_1_1Spatiogram.html</filename>
    <member kind="function">
      <type></type>
      <name>Spatiogram</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>ab643a2e7853629b8f09fa2eb9af834a8</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGrid, int binsize, ArrayGrid&lt; bool &gt; *pMaskGrid=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Spatiogram</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>ae8b225227a2d2e9439825a4d801037c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetBinValue</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>aa229a0d49311ac339492d4c28d23b7bd</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function">
      <type>common::Point&lt; double &gt;</type>
      <name>GetAveragePoint</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>a3f1d77f64dd460f7cb9aeccffdbaf82b</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetCovarianceMatrix</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>a71b8207d232d1cc9148a693f36ba0643</anchor>
      <arglist>(int binNr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Write</name>
      <anchorfile>classstira_1_1histogram_1_1Spatiogram.html</anchorfile>
      <anchor>a763752faf724678b5dc4636993d5ced0</anchor>
      <arglist>(std::string fileName, int threshold=100)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>sphericalCoord</name>
    <filename>structsphericalCoord.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::Statistics</name>
    <filename>classstira_1_1common_1_1Statistics.html</filename>
    <templarg></templarg>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetAverage</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a0603411927f0be01db327c87f7d32eaa</anchor>
      <arglist>(T *pData, int nrElements)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetAverage</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a7d494a97f5d1b986785aa7074899b938</anchor>
      <arglist>(std::vector&lt; T &gt; vData)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetVariance</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a356e0d394b212b14abe711f8d028bbf2</anchor>
      <arglist>(T *pData, int nrElements)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetVariance</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a8194aa8c5ba1fae554e3aa947fc0dc31</anchor>
      <arglist>(std::vector&lt; T &gt; vData)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetVariance</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a7b4b7afe2b416a169826b2c9f46bbd72</anchor>
      <arglist>(T *pData, int nrElements, double average)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetVariance</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a59998b8e4adae13155735b48daf58b7d</anchor>
      <arglist>(std::vector&lt; T &gt; vData, double average)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetCorrelation</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>aaa954aa4cce036dcec407d3caafa6cb7</anchor>
      <arglist>(double *pData1, double *pData2, int nrElements)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>GetCorrelation</name>
      <anchorfile>classstira_1_1common_1_1Statistics.html</anchorfile>
      <anchor>a5fcb7c844995dcc9ec17378a8ea65b84</anchor>
      <arglist>(std::vector&lt; double &gt; vData1, std::vector&lt; double &gt; vData2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::StegerLineDetector</name>
    <filename>classstira_1_1imageanalysis_1_1StegerLineDetector.html</filename>
    <member kind="function">
      <type></type>
      <name>StegerLineDetector</name>
      <anchorfile>classstira_1_1imageanalysis_1_1StegerLineDetector.html</anchorfile>
      <anchor>a6f7e1c811030be3ba62a65af2be40ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~StegerLineDetector</name>
      <anchorfile>classstira_1_1imageanalysis_1_1StegerLineDetector.html</anchorfile>
      <anchor>a8128b56eb4f6c153794cbe6ebb354b77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; bool &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1StegerLineDetector.html</anchorfile>
      <anchor>afb6499cfdb23cb2f068334851cd76fcd</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn, double sigmaSmooth, double lowerThreshold, double higherThreshold, bool isModeLight)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::StereoMatchDepth</name>
    <filename>classstira_1_1imageanalysis_1_1StereoMatchDepth.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::StringUtils</name>
    <filename>classstira_1_1common_1_1StringUtils.html</filename>
    <member kind="function">
      <type></type>
      <name>StringUtils</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a6761c9afec7ae7b11a911a72357d192f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~StringUtils</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a4d5f754d4be144d9d99619d091cb0a22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConvertIntegerToString</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a9a8e9c89e2d1df69f0c0c53ff2174ca8</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConvertFloatToString</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a36dc110b04a066574cfa6a99f42b6738</anchor>
      <arglist>(float f)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConvertDoubleToString</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>acfe477154c784afb6d25c4bab6eef950</anchor>
      <arglist>(double d)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConvertBoolToString</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a6331018a5f3517632da707c9cccc9fa3</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>ConvertStringToBoolean</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>ac174eb44a9649c25ab2a0e1275a345ff</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>ConvertStringToInt</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>affdff4b09097e1d8ff5a12505c8c7d5f</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static float</type>
      <name>ConvertStringToFloat</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a0fdf652e82db641c7cfc380a5aca0a66</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>ConvertStringToDouble</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a75501cc80b8b2d0b940207fd70d97ec0</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a36dba17b84fff5fc7120cd3e4d1854c7</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractFileNameRoot</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a72dcf1781dc8ed244591edb1875872c8</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static long int</type>
      <name>GetIndexFromFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a123e5d053ec428e12e6379a65cbada46</anchor>
      <arglist>(std::string inputString, bool useUnderscoreAsSeparator=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>FindFirstDot</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a709be270ab841c41f1cdf760efec3ab5</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>FindLastSlash</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a477c5cfd69898f51770970103f8c1e2e</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractFileExtension</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a051de1341ee345f458ed4580d8d63aaf</anchor>
      <arglist>(std::string inputString, bool includeDot=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractFilePrefix</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a6328bd4da18bc353c18163dc7158e9a4</anchor>
      <arglist>(std::string inputString, bool useUnderscoreAsSeparator=true)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractPathOfFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a98e46a78196ac706c4cead8e177f5e53</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ExtractFileNameFromPathPlusFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a57689a4d4e17842031afec13bddcfc15</anchor>
      <arglist>(std::string inputString)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConstructPathAndFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>aa4766d0b9f40cbade80bd65249f0094a</anchor>
      <arglist>(std::string path, std::string preFix, int indexNr, std::string extension)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>ConstructPathAndFileName</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a9eab8f97638a51e1ca2acf4242944733</anchor>
      <arglist>(std::string path, std::string preFix, int indexNr1, int indexNr2, std::string extension)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>SplitStringInIntegers</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>a24c20901a7d237cccbebb53490c0b27a</anchor>
      <arglist>(const std::string &amp;s, char c, std::vector&lt; int &gt; &amp;v)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::string</type>
      <name>GetCurrentTimeAsStringID</name>
      <anchorfile>classstira_1_1common_1_1StringUtils.html</anchorfile>
      <anchor>ae039698540a5ef9c00fe8804848eebf9</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::SubsampledTransform</name>
    <filename>classstira_1_1wavelet_1_1SubsampledTransform.html</filename>
    <base>stira::wavelet::Wavelet</base>
    <member kind="function">
      <type></type>
      <name>SubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1SubsampledTransform.html</anchorfile>
      <anchor>a88e5416376c55f8efb1ea8d5eba3c0fa</anchor>
      <arglist>(WaveletType type=DAUBECHIES_2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SubsampledTransform</name>
      <anchorfile>classstira_1_1wavelet_1_1SubsampledTransform.html</anchorfile>
      <anchor>ad9c7737f22ff558e895970e12991f2d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1wavelet_1_1SubsampledTransform.html</anchorfile>
      <anchor>a1417f552ceeb079b1dd75d2c58b21551</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceGrid, int nrScales)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1wavelet_1_1SubsampledTransform.html</anchorfile>
      <anchor>ad6963caf290bdfa0b44dc836757a635a</anchor>
      <arglist>(double threshold=0.0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SVD</name>
    <filename>classSVD.html</filename>
  </compound>
  <compound kind="class">
    <name>stira::common::TextFileUtils</name>
    <filename>classstira_1_1common_1_1TextFileUtils.html</filename>
    <member kind="function">
      <type></type>
      <name>TextFileUtils</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>ae2d4230edd496bfce78402f54f20362b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TextFileUtils</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>aca3498f01d7473ba534779e57a170ef3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Rows</type>
      <name>ReadTabSeparatedLineFromTextFile</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>a80dca0e93d3a6af6908036bae2b3c158</anchor>
      <arglist>(std::string inFileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; std::string &gt;</type>
      <name>ReadLinesFromTextFile</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>a15e6f67d3b20349333e927fd304ee93b</anchor>
      <arglist>(std::string inFileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>FilterText</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>ab967f2e33854c08bec0216785e188a16</anchor>
      <arglist>(std::string inFileName, std::string outFileName, int *pFilterValues, int filterLength, int nrColumnsToFilter, int nrOtherColumns)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SaveVectorOfValuesToTextFile</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>a89c52747a78154f87d08fe78cba85548</anchor>
      <arglist>(std::vector&lt; double &gt; inVector, std::string outFileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SaveVectorOfValuesToTextFile</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>a116dc58efb1c85978b73967f02ef96f7</anchor>
      <arglist>(std::vector&lt; int &gt; inVector, std::string outFileName)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>SaveVectorOfIntensityPointsToTextFile</name>
      <anchorfile>classstira_1_1common_1_1TextFileUtils.html</anchorfile>
      <anchor>a7fb9bab4ab0ff4c48b82bc4c63614e35</anchor>
      <arglist>(std::vector&lt; common::IntensityPoint &gt; inVector, std::string outFileName)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::TextureGenerator</name>
    <filename>classstira_1_1image_1_1TextureGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>TextureGenerator</name>
      <anchorfile>classstira_1_1image_1_1TextureGenerator.html</anchorfile>
      <anchor>a24cc03a9da66193bf62f641b65515057</anchor>
      <arglist>(int width, int height, TextureType myTextureType)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TextureGenerator</name>
      <anchorfile>classstira_1_1image_1_1TextureGenerator.html</anchorfile>
      <anchor>ad4d3267f10a495782db17b909d04d93f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GenerateMarble</name>
      <anchorfile>classstira_1_1image_1_1TextureGenerator.html</anchorfile>
      <anchor>a5ae3201196e4f89c612d0e9cee1e81f4</anchor>
      <arglist>(double xPeriod, double yPeriod, double turbPower, double turbSize)</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>GenerateWood</name>
      <anchorfile>classstira_1_1image_1_1TextureGenerator.html</anchorfile>
      <anchor>ae21c81f2872442abbff78cca3b9a9a42</anchor>
      <arglist>(double xyPeriod, double turbPower, double turbSize)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::Thinning</name>
    <filename>classstira_1_1imageanalysis_1_1Thinning.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>Thinning</name>
      <anchorfile>classstira_1_1imageanalysis_1_1Thinning.html</anchorfile>
      <anchor>aaf3c68d95f4b1342214b39234c9b663a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Thinning</name>
      <anchorfile>classstira_1_1imageanalysis_1_1Thinning.html</anchorfile>
      <anchor>a9d9ec1d2e80fc48de7b9b4e0c3d98efe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>RunThinning</name>
      <anchorfile>classstira_1_1imageanalysis_1_1Thinning.html</anchorfile>
      <anchor>a8c8467501e53e44746e1ae864067a156</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, common::RectangularROI&lt; int &gt; rroi, T value)</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; T &gt; *</type>
      <name>RunPruning</name>
      <anchorfile>classstira_1_1imageanalysis_1_1Thinning.html</anchorfile>
      <anchor>ae8734c56e5b02c0ff773fa88d8d4adb8</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *pGridIn, common::RectangularROI&lt; int &gt; rroi, T value)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::TikhonovMillerDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</filename>
    <base>stira::deconvolve::IterativeDeconvolve</base>
    <member kind="function">
      <type></type>
      <name>TikhonovMillerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a451e6c904bed8b80de449a0e758145fc</anchor>
      <arglist>(Image *pDegradedImage, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TikhonovMillerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a303deb1c7192c1eb9ff6fbc0af6f3220</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TikhonovMillerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a86e2f0db9668a7205fe7cace24dc4c3a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEnforcePositivity</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a89aab84fa31773908e77236e9916abd3</anchor>
      <arglist>(bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetEnforcePositivity</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>ab3f61bbb62c12be8a676167ff78ba32d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a6a86ddd4ad857537fb01c46dd90c71cf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1deconvolve_1_1TikhonovMillerDeconvolve.html</anchorfile>
      <anchor>a2bad7ed5a58d9adacc0ad2692c8e4430</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::fouriertools::TransferFunctionGenerator</name>
    <filename>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>TransferFunctionGenerator</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a333429db683153e12fe8bee0b11f4bba</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TransferFunctionGenerator</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a38d9c3f08614a61a3e901971e967eede</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>GetScaleFactors</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a0f69bd6308b2a6156a0109fe4055a1f7</anchor>
      <arglist>(int width, int height, double &amp;xFactor, double &amp;yFactor)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateHighPassTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a3b1cf202002448ea21bae9c1a30cc640</anchor>
      <arglist>(int width, int height, double x1, double x2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateLowPassTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a88935685171efeca527b6724c5c35243</anchor>
      <arglist>(int width, int height, double x1, double x2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FFTBand *</type>
      <name>GenerateOrientedTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>ab2b794cfcda94de6471b7e23744e08b5</anchor>
      <arglist>(int width, int height, int orientationIndex, int maxNrOfOrientations, bool isForward, common::NumberMode mode=common::MODE_REAL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>HighFrequencyCrossMask</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>aeca02312ad0dd347efb0fcd4aabbd085</anchor>
      <arglist>(FFTBand *inoutGrid, int nrBands)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateLogRadiusBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>ab8242b4a58385999af592d4d313b9431</anchor>
      <arglist>(int width, int height, double centerFrequency, double bandWidth)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateGaussianAngularBand</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a065c2679d663f0dc5b07123a03118181</anchor>
      <arglist>(int width, int height, double centerAngle, double angleSpread)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateLogGaborBandTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>aed54ab657229b20fd6bf65476c4872d3</anchor>
      <arglist>(int width, int height, double centerFrequency, double radialWidth, double centerAngle, double angleSpread)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>GenerateAxisSuppressTransferFunction</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>ab27461c7280dca12079965308bc06448</anchor>
      <arglist>(int width, int height, int axisWidth, double x1, double x2)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ConvertTransferFunctionToFilterKernel</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a0d07e9e4b0ef63a8100d24ca2d05c834</anchor>
      <arglist>(FFTBand *pTransferFunction, common::NumberMode mode=common::MODE_REAL)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>ConvertTransferFunctionToFilterKernel</name>
      <anchorfile>classstira_1_1fouriertools_1_1TransferFunctionGenerator.html</anchorfile>
      <anchor>a26078ddf7d2b3be25f43ba9288faf3e3</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pTransferFunction, common::NumberMode mode=common::MODE_REAL)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imagedata::color::TransformColorSpace</name>
    <filename>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</filename>
    <member kind="function">
      <type></type>
      <name>TransformColorSpace</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a70e140a7a415be6f7e3d04fe71c45ea6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TransformColorSpace</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a110a396d969504f5ed8a59be1bf34396</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxColorValue</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>aed81fae15987a4b4ef5da23fc4c39e54</anchor>
      <arglist>(double maxColorValue)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetReferenceWhite</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ac0680b5f4a73ec195a12197fd6411894</anchor>
      <arglist>(ColorValue referenceWhite)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>GetReferenceWhite</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a94e3c41853dcde65abedc89d1b649289</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>sRGBtoXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a64afa6cc3b7d70d0119d104230f73163</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>XYZtosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a9d296169a20b89f98962a32739daa63f</anchor>
      <arglist>(ColorValue xyzValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdobeRGBtoXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a77650884066931a5ff4da426de8fcc0d</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>XYZtoAdobeRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a412c4f31510847b90466c75cbec79830</anchor>
      <arglist>(ColorValue xyzValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>sRGBtoLuv</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a984bfc2305ee4e22bb01ca01802106ef</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LuvtosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a6e49d6f1db9e064ff1bc799fd5a5d44a</anchor>
      <arglist>(ColorValue luvValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>XYZtoLuv</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a61a7a1c383f47d1a7cf91bebabce3341</anchor>
      <arglist>(ColorValue xyzValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LuvtoXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>acfb9379d1f7ce8cd43df4568c1d870ec</anchor>
      <arglist>(ColorValue luvValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>sRGBtoLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a74a59b2abf3847aae25e7c56ac6f18cb</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LabtosRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a42c8c0f744acd3898cc8e853714116d9</anchor>
      <arglist>(ColorValue luvValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>AdobeRGBtoLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a08696101472380a5ae17530e04c8e42d</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LabtoAdobeRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a56d5ed3b31dad07ead11837d21785687</anchor>
      <arglist>(ColorValue luvValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>XYZtoLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ac54aa3533795e4ad030d4c3722182e87</anchor>
      <arglist>(ColorValue xyzValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LabtoXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a5a62d0cdf3c53549c34bce987e6d2c4c</anchor>
      <arglist>(ColorValue labValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>RGBtoCMY</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a3bda9309d0c379709a4e944d5b3b92c8</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>CMYtoRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ad357196eb70dc59c50ca53409a628651</anchor>
      <arglist>(ColorValue cmyValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>RGBtoHSV</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ac906fe996c782d9e33c8450d6befd96f</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>HSVtoRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a5234740d4d4eca2cc9801ee2a2cb50db</anchor>
      <arglist>(ColorValue hsvValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>RGBtoHSI</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a9eae9051d452dd215134857b78cdf057</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>HSItoRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>aca8d4da87f6204fb3e84601ac8e99787</anchor>
      <arglist>(ColorValue hsiValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>RGBtoHSL</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a55656406287c6d43c405f959e632dac5</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>HSLtoRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a4647081a749a73fd0a86f3f32be28381</anchor>
      <arglist>(ColorValue hslValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LabtoLCH</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a8306b373c20a9aecbcfbf18d761bdf64</anchor>
      <arglist>(ColorValue labValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>LCHtoLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a42b0550eb73bb162b03d59234ab4ae62</anchor>
      <arglist>(ColorValue lchValue)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>SpectralValuesToXYZ</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>aaf75d51b645d198053ac64cfacb3aec5</anchor>
      <arglist>(double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax)</arglist>
    </member>
    <member kind="function">
      <type>ColorValue</type>
      <name>SpectralValuesToLab</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>af432c5d71322ec8b243fc23c482ceaba</anchor>
      <arglist>(double *pSpectralValuesArray, int wavelengthMin, int wavelengthMax)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DeltaE1976</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>afd3bef37536f0a908b025e493ba252f7</anchor>
      <arglist>(ColorValue lab1, ColorValue lab2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DeltaE1994</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a33694c488b63eb98db474aa0a7f189f0</anchor>
      <arglist>(ColorValue lab1, ColorValue lab2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DeltaE2000</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a64537eae48dc8c18111a72882c4f7f54</anchor>
      <arglist>(ColorValue lab1, ColorValue lab2)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>DeltaE2000</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ac19183d59349a3404be3d6053d87e221</anchor>
      <arglist>(double *pSpectralValues1, double *pSpectralValues2, int wavelengthMin, int wavelengthMax)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>RGBtoYUV</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ad16ee3bf1d2f9a6e4cd1cc1b0d93a117</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>YUVtoRGB</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>ac3f8195e23e2c172b0cb2d5f9b3f189e</anchor>
      <arglist>(ColorValue yuvValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double</type>
      <name>RGBToGray</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a242b8a2b0ad538ea0eb0366489998bd8</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>RGBToSepia</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a4ba8675296f56872335f9c1903ed38e7</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>RGBToSepia2</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>aed15ca79a5a7696d3e828064b23962ef</anchor>
      <arglist>(ColorValue rgbValue)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ColorValue</type>
      <name>RGBToSepia2</name>
      <anchorfile>classstira_1_1imagedata_1_1color_1_1TransformColorSpace.html</anchorfile>
      <anchor>a23dfee915d179957c0a4ee68aee30a7d</anchor>
      <arglist>(double grayValue)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::image::Translation</name>
    <filename>classstira_1_1image_1_1Translation.html</filename>
    <base>stira::image::GeometricTransform</base>
    <member kind="function">
      <type></type>
      <name>Translation</name>
      <anchorfile>classstira_1_1image_1_1Translation.html</anchorfile>
      <anchor>a63b5ce9219c974d88347c56eff79fa09</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Translation</name>
      <anchorfile>classstira_1_1image_1_1Translation.html</anchorfile>
      <anchor>a0292db5fc3cffb887f549df454ebee89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaX</name>
      <anchorfile>classstira_1_1image_1_1Translation.html</anchorfile>
      <anchor>a25fca7d55532012845f812de65bf6ed8</anchor>
      <arglist>(double dx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeltaY</name>
      <anchorfile>classstira_1_1image_1_1Translation.html</anchorfile>
      <anchor>a1138eb453def5de343b54eeff40b951b</anchor>
      <arglist>(double dy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::filter::UnsharpMask</name>
    <filename>classstira_1_1filter_1_1UnsharpMask.html</filename>
    <member kind="function">
      <type></type>
      <name>UnsharpMask</name>
      <anchorfile>classstira_1_1filter_1_1UnsharpMask.html</anchorfile>
      <anchor>a56eb4d33f64ce65d554f88a398925822</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~UnsharpMask</name>
      <anchorfile>classstira_1_1filter_1_1UnsharpMask.html</anchorfile>
      <anchor>a05d1bc20b7004122cca0f73f7c765a51</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::VanCittertLandweberDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</filename>
    <base>stira::deconvolve::IterativeDeconvolve</base>
    <member kind="function">
      <type></type>
      <name>VanCittertLandweberDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>a16e9bec09d42115ed2a827c166e60de6</anchor>
      <arglist>(Image *pDegradedImage, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VanCittertLandweberDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>adf539d6b1b05b71f079c901577286656</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF, int maxNrOfIterations=20)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~VanCittertLandweberDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>a3615a4895497dde2f018ed6659696b62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEnforcePositivity</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>a8f05c1501606ffcb6455d503fb86a311</anchor>
      <arglist>(bool flag)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>GetEnforcePositivity</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>aa73b734a56c4bef780acb5a1934c8d3b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>deconvolutionType</type>
      <name>GetDeconvolutionType</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>a5cb1eb0b744aeb566d1c0b1f65c42b88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetDeconvolutionType</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>ac6fb093d8f9dc0d0c21ec10435bc2365</anchor>
      <arglist>(deconvolutionType myType)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>a54edb146226dc24504b9da22324506fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>PrintParameters</name>
      <anchorfile>classstira_1_1deconvolve_1_1VanCittertLandweberDeconvolve.html</anchorfile>
      <anchor>addce021420dcfe82961039abb10848ad</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::WatershedMeyer</name>
    <filename>classstira_1_1imageanalysis_1_1WatershedMeyer.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>WatershedMeyer</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>aa0ed8ce0f8005ae9eadfadbb4522c9f2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WatershedMeyer</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a6be4f6f03760360e27cf4d6207fd0382</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetMaxMinimaLevel</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a49c3e97234cb7a35c14c66e22d717c5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetMaxMinimaLevel</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a2243f83a2e5f0a66199aec37a7fa5141</anchor>
      <arglist>(double maxLevel)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>GetEqualityPrecision</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a652c9c984e06a664b70c83edf27a70b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetEqualityPrecision</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a7b8c339fd8f7c207739574e501564ba3</anchor>
      <arglist>(double precision)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ab1bf89f20c6e6876c681eab759858b2a</anchor>
      <arglist>(ArrayGrid&lt; T &gt; *iInputImage, bool usegradientImage, std::string sourceDataName=std::string(&quot;&quot;))</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfWatershedPixels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ac65e6bd7b6615b5b54344f1274a856c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; bool &gt; *</type>
      <name>GetWatershedGrid</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ab92fe72aeb1278137352a0821614d938</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfLabels</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ae59760ea43789fc7db793dc793829198</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; int &gt; *</type>
      <name>GetLabelImage</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ad84be0fa38f32c24b114e184a6947730</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>CreateLabelsRidgeImage</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a0947ec35751ea470848dbe9f46e6148d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Image *</type>
      <name>CreateLabelsIntensitiesImage</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a0222921e0e11b4ba92cb75457deae0dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsElementNoMinima</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>ab20ac0cec79b44ff5cc0701067ffef77</anchor>
      <arglist>(PixelElement&lt; T &gt; pe1, PixelElement&lt; T &gt; pe2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsElementSame</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a05a405390ed317f354e2999a07599d2e</anchor>
      <arglist>(PixelElement&lt; T &gt; pe1, PixelElement&lt; T &gt; pe2)</arglist>
    </member>
    <member kind="function">
      <type>PixelElement&lt; T &gt;</type>
      <name>CreatePixelElement</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a0801346ebca8819013d6a020d04608b3</anchor>
      <arglist>(int x, int y)</arglist>
    </member>
    <member kind="function">
      <type>PixelElement&lt; T &gt;</type>
      <name>CreatePixelElement</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a17f3c4ffea6fb7aec992435fb2654e54</anchor>
      <arglist>(stira::common::Point&lt; int &gt; pt)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsValidNeighbour</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedMeyer.html</anchorfile>
      <anchor>a70d3965453f29664a7169469af8fd1a1</anchor>
      <arglist>(int x, int y, int dx, int dy)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::imageanalysis::WatershedToboggan</name>
    <filename>classstira_1_1imageanalysis_1_1WatershedToboggan.html</filename>
    <member kind="function">
      <type></type>
      <name>WatershedToboggan</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedToboggan.html</anchorfile>
      <anchor>a6e32aa52383e358d32129677da7c985c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WatershedToboggan</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedToboggan.html</anchorfile>
      <anchor>a451b7ccfaedfd4535635c3adc77beb9f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; int &gt; *</type>
      <name>Run</name>
      <anchorfile>classstira_1_1imageanalysis_1_1WatershedToboggan.html</anchorfile>
      <anchor>ac15a9b9fe2531d56733a2bee62435fd1</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pGridIn)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::Wavelet</name>
    <filename>classstira_1_1wavelet_1_1Wavelet.html</filename>
    <member kind="function">
      <type></type>
      <name>Wavelet</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a5a1a7011a9343298bfe398e60888c681</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Wavelet</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a0e2729f4abab63f8ed6cbd558f1b283a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Decompose</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ade4334fad44c2701d11e9630fdbf019a</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceGrid, int nrScales)=0</arglist>
    </member>
    <member kind="function">
      <type>Pyramid&lt; double &gt; *</type>
      <name>GetPyramid</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ab75382cafef32eb2a64bea04a3e3aaf2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>Reconstruct</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a347bd31b9965438761438eac3b339c85</anchor>
      <arglist>(double threshold=0.0)=0</arglist>
    </member>
    <member kind="function">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>GetCopyOfReconstructedGrid</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a874075d49e873d0ae2f3d803e5705b32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfOrientations</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>abaee7b45ac030b9cfa8665a100eaadac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetNumberOfScales</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ad47b5ca4a33f7162aff8412486ca1392</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a89078b790a7d7b744e894799209b8aca</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pSourceGrid, int nrScales, int nrOrientations=3, bool createBands=false, bool isSubsampled=true, bool isLowestScaleSubsampled=true)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrOrientations</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a05e233ed56fc4cd76d7d2c85572ac526</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mNrScales</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ab738a348c0d0e2d15cb135b2a8bbd11f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Pyramid&lt; double &gt; *</type>
      <name>mpPyramid</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>acb5ef67a8a967e8989efd2ccc27286cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpDecomposeReconstructGrid</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ad4beb93cf15038e103ece7b64ced5250</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>mCurrentScale</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>a2f32b1775b477e60db7509221c7ddfa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>WaveletFilterSet</type>
      <name>mSet</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>adcbc77e0448b90bd957bb383ee2a00b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ArrayGrid&lt; double &gt; *</type>
      <name>mpSourceGrid</name>
      <anchorfile>classstira_1_1wavelet_1_1Wavelet.html</anchorfile>
      <anchor>ae470b732e1f81b828e8a557e04b71998</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stira::wavelet::WaveletFilterSet</name>
    <filename>structstira_1_1wavelet_1_1WaveletFilterSet.html</filename>
    <member kind="variable">
      <type>double *</type>
      <name>pLowpassForward</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>a7d22485cecebc09a08cd9dec2f5781e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>pLowpassInvers</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>aa8016b8266a2e9ad017f89c5d9273eb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>pHighpassForward</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>acf86b17810141efc5539fd01dc9d4979</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double *</type>
      <name>pHighpassInvers</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>a2b35cf3f39e0591a6b80771d37d7abce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>length</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>a23c6cc0889bfaba67d704180abb5b232</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WaveletType</type>
      <name>type</name>
      <anchorfile>structstira_1_1wavelet_1_1WaveletFilterSet.html</anchorfile>
      <anchor>af4b909bde55ba7e5d3f4412d72bd2544</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::wavelet::WaveletTapGenerator</name>
    <filename>classstira_1_1wavelet_1_1WaveletTapGenerator.html</filename>
    <member kind="function">
      <type></type>
      <name>WaveletTapGenerator</name>
      <anchorfile>classstira_1_1wavelet_1_1WaveletTapGenerator.html</anchorfile>
      <anchor>a95872a6cb3c660cd6cb06e5fc00fb6d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WaveletTapGenerator</name>
      <anchorfile>classstira_1_1wavelet_1_1WaveletTapGenerator.html</anchorfile>
      <anchor>a62c5adae9208b3a5b83572999c7ce7eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>WaveletFilterSet</type>
      <name>Generate</name>
      <anchorfile>classstira_1_1wavelet_1_1WaveletTapGenerator.html</anchorfile>
      <anchor>a77654b723570efdd3e14e267bcafe680</anchor>
      <arglist>(WaveletType type)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>stira::deconvolve::WienerDeconvolve</name>
    <filename>classstira_1_1deconvolve_1_1WienerDeconvolve.html</filename>
    <base>stira::deconvolve::DeconvolveMaster</base>
    <member kind="function">
      <type></type>
      <name>WienerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1WienerDeconvolve.html</anchorfile>
      <anchor>a216972ed6a6dbd7dedd0280d663b5d79</anchor>
      <arglist>(Image *pDegradedImage)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>WienerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1WienerDeconvolve.html</anchorfile>
      <anchor>a57769dac922a7d4dc329bce56cae740f</anchor>
      <arglist>(Image *pDegradedImage, Image *pPSF)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~WienerDeconvolve</name>
      <anchorfile>classstira_1_1deconvolve_1_1WienerDeconvolve.html</anchorfile>
      <anchor>a1ec844bb7ce518b999cc372914e0e2b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>Run</name>
      <anchorfile>classstira_1_1deconvolve_1_1WienerDeconvolve.html</anchorfile>
      <anchor>a6b985a0d13e1b41919298f635823e38b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static ArrayGrid&lt; double &gt; *</type>
      <name>RunSingleband</name>
      <anchorfile>classstira_1_1deconvolve_1_1WienerDeconvolve.html</anchorfile>
      <anchor>aa7d9ff8d8d46d7198c8425b282bdff61</anchor>
      <arglist>(ArrayGrid&lt; double &gt; *pInGrid, ArrayGrid&lt; double &gt; *pInPSF, double noiseLevel)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>stira</name>
    <filename>namespacestira.html</filename>
    <class kind="class">stira::FlashROF</class>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>STIRA (old name FRIEP) Simple Toolkit for Image Restoration and Analysis</title>
    <filename>index</filename>
  </compound>
</tagfile>
