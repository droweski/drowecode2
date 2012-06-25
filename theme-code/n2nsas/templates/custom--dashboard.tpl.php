<?php

/**
 * @file
 * Custom template for the dashboard page.
 *
 */
?>

<div id="page">
  
  <?php if ($logo || $site_name || $site_slogan || $page['header']): ?>
    <header id="header" role="banner">
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if ($site_name): ?>
          <h1 id="site-name">
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
          </h1>
      <?php endif; ?>

      <?php if ($site_slogan): ?>
        <div id="site-slogan"><?php print $site_slogan; ?></div>
      <?php endif; ?>

      <?php print render($page['header']); ?>
    </header><!-- /#header -->
  <?php endif; ?>
  
  <?php if ($main_menu_links): ?>
    <nav id="main-menu" role="navigation">
      <?php print $main_menu_links; ?>
    </nav><!-- /#navigation -->
  <?php endif; ?>

  <?php if ($secondary_menu_links): ?>
    <nav id="secondary-menu" role="navigation">
      <?php print $secondary_menu_links ?>
    </nav> <!-- /#secondary-menu -->
  <?php endif; ?>

  <?php if ($page['featured']): ?>
    <div id="featured">
      <?php print render($page['featured']); ?>
    </div><!-- /#featured -->
  <?php endif; ?>

  <div id="main">
    <?php if ($page['highlighted']): ?>
      <div id="highlighted">
        <?php print render($page['highlighted']); ?>
      </div><!-- /#highlighted -->
    <?php endif; ?>
 
<!-- remove breadcrumb display -->
    <?php if($node->type !== 'dashboard'): ?>
      <?php if ($breadcrumb): ?>
        <div id="breadbox">
          <?php print $breadcrumb; ?>
        </div>
      <?php endif; ?>
    <?php endif; ?>

<!-- removed title display -->
  
    <?php if ($tabs): ?>
      <div class="tabs"><?php print render($tabs); ?></div>
    <?php endif; ?>
    <?php print $messages; ?>
    <?php print render($page['help']); ?>
    <?php if ($action_links): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>

    <?php print render($page['content_top']); ?>
    <?php print render($page['content']); ?>
    <?php print render($page['content_bottom']); ?>

    <?php print $feed_icons; ?>
  </div><!-- /#main -->

  <?php if ($page['sidebar_first']): ?>
    <aside id="sidebar-first" role="complementary">
      <?php print render($page['sidebar_first']); ?>
    </aside><!-- /#sidebar-first -->
  <?php endif; ?>

  <?php if ($page['sidebar_second']): ?>
    <aside id="sidebar-second" role="complementary">
      <?php print render($page['sidebar_second']); ?>
    </aside><!-- /#sidebar-second -->
  <?php endif; ?>

  <?php if ($page['footer']): ?>
    <footer id="footer" role="contentinfo">
      <?php print render($page['footer']); ?>
    </footer><!-- /#footer -->
  <?php endif; ?>

</div><!-- /#page -->
