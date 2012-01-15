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
  
  $alias = new provisionConfig_drushrc_alias($context);
  provision_file()->chmod($alias->filename(), '440');

  if (d()->context_type == 'site') {
    $drushrc = new provisionConfig_drushrc_site($context);
    provision_file()->chmod($drushrc->filename(), '440');
  }
}