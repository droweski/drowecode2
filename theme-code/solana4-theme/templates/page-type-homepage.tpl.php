<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
    <?php print $scripts; ?>
  </head>

  <body class="<?php print $body_classes; ?>">
    <div id="skip"><a href="#content"><?php print t('Skip to Content'); ?></a> <a href="#navigation"><?php print t('Skip to Navigation'); ?></a></div>  
    <div id="page">

    <!-- ______________________ HEADER _______________________ -->

    <div id="header">

      <div id="logo-box">
        <?php if (!empty($logo)): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
            <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
          </a>
        <?php endif; ?>
      </div> <!-- /logo-box -->

      <div id="links-box">
        <?php if (!empty($primary_links) || !empty($secondary_links)): ?>
          <div id="navigation" class="menu <?php if (!empty($primary_links)) { print "with-main-menu"; } if (!empty($secondary_links)) { print " with-sub-menu"; } ?>">
            <?php if (!empty($primary_links)){ print theme('links', $primary_links, array('id' => 'primary', 'class' => 'links main-menu')); } ?>
            <?php if (!empty($secondary_links)){ print theme('links', $secondary_links, array('id' => 'secondary', 'class' => 'links sub-menu')); } ?>
          </div> <!-- /navigation -->
        <?php endif; ?>
      </div> <!-- /links-box -->

      <div id="search-widget">
      <?php print $search_box; ?>
      </div> <!-- /search-widget -->

      </div> <!-- /header -->

      <div id="menubar">
        <?php if ($menubar): ?>
          <div id="menubar-region">
            <?php print $menubar; ?>
          </div>
        <?php endif; ?>
      </div> <!-- /menubar -->

      <!-- ______________________ MAIN _______________________ -->

      <div id="main" class="clearfix">
        <div id="content">
          <div id="content-inner" class="inner column center">
            <div class="slide-frame">
             <div id="content-area">
               <?php print $content; ?>
             </div> <!-- /#content-area -->
            </div> <!-- /#slide-frame -->
            <div id="content-bottom" class="clearfix">
              <?php print $content_bottom; ?>
            </div><!-- /#content-bottom -->
          </div>
        </div> <!-- /content-inner /content -->
      </div> <!-- /main -->

      <!-- ______________________ FOOTER _______________________ -->
      <div id="footer">
        <?php print $footer_message; ?>
        <?php print $footer_block; ?>
      </div> <!-- /footer -->

    </div> <!-- /page -->
    <?php print $closure; ?>
  </body>
</html>