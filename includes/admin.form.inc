<?php

/**
 * @file
 * includes/admin.form.inc
 *
 * Module admin form.
 */

/**
 * Module admin form.
 */
function islandora_compound_object_admin_form($form, &$form_state) {
  $form = array();

  $form['islandora_compound_object_compound_children'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only allow compound objects to have child objects associated with them'),
    '#description' => t('If unchecked, all objects may have child objects.'),
    '#default_value' => variable_get('islandora_compound_object_compound_children', TRUE),
  );

  $form['islandora_compound_object_thumbnail_child'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a thumbnail for compound objects from their first child'),
    '#description' => t('If checked, the thumbnail for a compound object will be generated from its first child object.'),
    '#default_value' => variable_get('islandora_compound_object_thumbnail_child', TRUE),
  );

  $form['islandora_compound_object_hide_child_objects_ri'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide child objects in RI results'),
    '#description' => t('If checked, child objects will be hidden. Only visible within the compound context.'),
    '#default_value' => variable_get('islandora_compound_object_hide_child_objects_ri', TRUE),
  );

  $form['islandora_compound_object_hide_child_objects_solr'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide child objects in Solr results'),
    '#description' => t('If checked, child objects will be hidden. Only visible within the compound context.'),
    '#default_value' => variable_get('islandora_compound_object_hide_child_objects_solr', TRUE),
  );

  $form['islandora_compound_object_solr_fq'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr filter query'),
    '#description' => t('Filter compound object children from Solr results.'),
    '#default_value' => variable_get('islandora_compound_object_solr_fq', '-RELS_EXT_isConstituentOf_uri_mt:*'),
    '#element_validate' => array('islandora_compound_object_solr_fq_validate'),
    '#states' => array(
      'visible' => array(
        ':input[name="islandora_compound_object_hide_child_objects_solr"]' => array('checked' => TRUE),
      ),
      'required' => array(
        ':input[name="islandora_compound_object_hide_child_objects_solr"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['islandora_compound_object_relationship'] = array(
    '#type' => 'textfield',
    '#title' => t('Child relationship predicate'),
    '#description' => t('Changing this after objects have been created will break functionality. Should be part of info:fedora/fedora-system:def/relations-external#'),
    '#default_value' => variable_get('islandora_compound_object_relationship', 'isConstituentOf'),
    '#required' => TRUE,
  );

  $form['islandora_compound_object_use_jail_view'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use alternative, autoloading display for compounds?'),
    '#description' => t('<b>Requires</b> <a href="@url">JAIL</a> library to be present.', array(
      '@url' => url('https://github.com/sebarmeli/JAIL', array('absolute' => TRUE)),
    )),
    '#default_value' => variable_get('islandora_compound_object_use_jail_view', FALSE),
    '#element_validate' => array('islandora_compound_object_admin_form_jail_validation'),
  );
  return system_settings_form($form);
}

/**
 * Check if the JAIL is available.
 *
 * @param array $element
 *   The element to check.
 * @param array $form_state
 *   The Drupal form state.
 * @param array $form
 *   The Drupal form definition.
 */
function islandora_compound_object_admin_form_jail_validation(array $element, array &$form_state, array $form) {
  if ($element['#value'] == 1 && !libraries_get_path('JAIL')) {
    $element['#value'] = 0;
    form_set_value($element, $element['#value'], $form_state);
    drupal_set_message(t('The <a href="@url">JAIL</a> library must be present in the libraries folder to use this display.', array(
      '@url' => url('https://github.com/sebarmeli/JAIL', array('absolute' => TRUE)),
    )), 'error');
  }
}

/**
 * Solr fq element state validation callback.
 *
 * @param array $element
 *   The form element.
 * @param array $form_state
 *   The form state.
 */
function islandora_compound_object_solr_fq_validate($element, &$form_state) {
  if ($form_state['values']['islandora_compound_object_hide_child_objects_solr'] &&
    empty($form_state['values']['islandora_compound_object_solr_fq'])) {
    form_error($element, t('Solr filter query field is required.'));
  }
}
