<div class = "follow-link">
	<a href = "http://instagram.com/ginkgotshirts" target="_blank"><?php print t('Follow Ginkgo on Instagram')?></a>
</div>
<div class="connected-carousels">
  <div class="stage">
  	<div class="carousel carousel-stage">
  		<ul>
  			<?php foreach ($images as $value): ?>
					<?php
						$image = $value->images;
						$comments = $value->comments->data;
						$caption = $value->caption;
						$user = $value->user;
					?>
					<li>
						<a href = "<?php print $value->link; ?>" target = "_blank"><img src = "<?php print $image->standard_resolution->url; ?>" /></a>
						<div class = "comment-wrapper">
							<?php if (!empty($user)): ?>
								<div class = "caption">
									<span>
										<span class = "user-picture">
											<img src = "<?php print $user->profile_picture; ?>" />
										</span>
										<span class = "user-name"><?php print $user->full_name; ?></span>
										<?php if (!empty($caption)): ?>
											<span class = "comment-text"><?php print $caption->text; ?></span>
										<?php endif; ?>
										<span class = "time-text"><?php print date('m-d-Y',$value->created_time); ?></span>
									</span>
								</div>
							<?php endif;?>
							<?php foreach ($comments as $comment): ?>
								<span>
									<span class = "user-picture">
										<img src = "<?php print $comment->from->profile_picture; ?>" />
									</span>
									<span class = "user-name"><?php print $comment->from->username; ?></span>
									<span class = "comment-text"><?php print $comment->text; ?></span>
								</span>
							<?php endforeach; ?>
						</div>	
					</li>
				<?php endforeach; ?>
  		</ul>
  	</div>
  	<a href="#" class="prev prev-stage"><span>&lsaquo;</span></a>
    <a href="#" class="next next-stage"><span>&rsaquo;</span></a>
  </div>
  <div class="navigation">
  	<a href="#" class="prev prev-navigation">&lsaquo;</a>
    <a href="#" class="next next-navigation">&rsaquo;</a>
    <div class="carousel carousel-navigation">
	    <ul>
	      <?php foreach ($images as $value): ?>
					<?php $image = $value->images; ?>
					<li>
						<img width = "50px" height = "50px" src = "<?php print $image->standard_resolution->url; ?>" />
					</li>
				<?php endforeach; ?>
	    </ul>
    </div>
  </div>
</div>