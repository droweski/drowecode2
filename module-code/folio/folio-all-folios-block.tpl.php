<?php

/**
 * @file
 * Default theme implementation for rendering folio outlines within a block.
 * This template is used only when the block is configured to "show block on
 * all pages" which presents Multiple independent folios on all pages.
 *
 * Available variables:
 * - $folio_menus: Array of folio outlines keyed to the parent folio ID. Call
 *   render() on each to print it as an unordered list.
 */
?>
<?php foreach ($folio_menus as $folio_id => $menu): ?>
  <div id="folio-block-menu-<?php print $folio_id; ?>" class="folio-block-menu">
    <?php print render($menu); ?>
  </div>
<?php endforeach; ?>
