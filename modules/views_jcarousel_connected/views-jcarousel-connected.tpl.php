<?php
/**
 * @file views-isotope.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<div class = "connected-carousels" id = "view-<?php print $dom_id; ?>">
  <?php if (count($rows) >= 0): ?>
    <div class = "stage">
      <div class="carousel carousel-stage">
        <ul>
          <?php foreach ($rows as $key => $row): ?>
            <?php if ($key == 0): ?>
              <li class = "<?php print $classes_array[$key]; ?>"><?php print $row; ?></li>
            <?php endif; ?>
          <?php endforeach; ?>
        </ul>
      </div>
    </div>
  <?php endif; ?>
  <?php if (count($pager_control) >= 2 || count($rows) >=2 ): ?>
    <div class="navigation">
      <a href="#" class="prev prev-navigation">&lsaquo;</a>
      <a href="#" class="next next-navigation">&rsaquo;</a>
      <div class="carousel carousel-navigation">
        <ul>
          <?php if (!empty($pager_control)): ?>
            <?php foreach ($pager_control as $key => $row): ?>
              <?php if ($key != 0): ?>
                <li class = "pager-item"><?php print $row; ?></li>
              <?php endif ;?>
            <?php endforeach; ?>
          <?php else: ?>
            <?php foreach ($rows as $key => $row): ?>
              <?php if ($key != 0): ?>
                <li class = "pager-item"><?php print $row; ?></li>
              <?php endif ;?>
            <?php endforeach; ?>
          <?php endif; ?>
        </ul>
      </div>
    </div>
  <?php endif; ?>
</div>