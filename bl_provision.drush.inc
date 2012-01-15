<?php

function bl_provision_drush_exit() {
  $command = drush_get_command();
  $command = explode(" ", $command['command']);

  if (preg_match("/^provision-(verify|install)$/", $command[0])) {
    bl_provision_set_perms();
  }
}

function bl_provision_set_perms() {
  drush_log(dt('Setting file permissions for brightlemon dev team.'));
  $context = d()->name;
  
  $settings = new provisionConfig_drupal_settings($context);
  $alias = new provisionConfig_drushrc_alias($context);

  switch (d()->context_type) {
    case 'site':
      $drushrc = new provisionConfig_drushrc_site($context);
      break;
    case 'platform':
      $drushrc = new provisionConfig_drushrc_platform($context);
      break;
    case 'server':
      $drushrc = new provisionConfig_drushrc_server($context);
      break;
  }

  provision_file->chmod($drushrc->filename(), '440');
  provision_file->chmod($alias->filename(), '440');
  provision_file->chmod($settings->filename(), '440');
}