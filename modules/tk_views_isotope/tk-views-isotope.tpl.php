<?php
/**
 * @file views-isotope.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if(!empty($list_filter)): ?>
  <div class = "isotop-filter">
    <?php foreach ($list_filter as $id => $filter): ?>
      <div class="filter-row<?php print $id; ?>">
        <ul class="inline" id="<?php print $filter; ?>">
          <li class="element-filter"><a href="#<?php print $filter; ?>" class = "filter active" data-filter="*"><?php print t('All'); ?></a></li>
          <?php foreach ($filters[$filter] as $key => $element): ?>
            <li class="element-filter">
              <a href="#<?php print $filter; ?>" data-filter=".<?php print $key; ?>" class = "filter"><?php print $element; ?></a>
            </li>

          <?php endforeach; ?>
        </ul>
      </div>
    <?php endforeach; ?>
  </div>
<?php endif; ?>


<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<ul class = "gallery-isotope <?php print($ul_class); ?>" id="<?php print $isotop_id; ?>">
  <?php
    foreach ($rows as $id => $row):
  ?>
	<li class="<?php if (!empty($data_filter[$id])) print ($data_filter[$id]); ?> isotope-element <?php print $classes_array[$id]; ?>">
  	<?php print $row; ?>
  </li>
  <?php
    endforeach;
  ?>
</ul>