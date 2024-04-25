<?php

function show_attr($attrs, &$result, $depth=0, $carry='', $tr = '<tr>', $td = '<td>'){
  if ( !is_array($attrs) || sizeof($attrs) < 1 ){
    return is_array($attrs) ? '' : $attrs .'</td></tr>';
  }

  foreach ($attrs as $key => $value) {
    if (is_array($value)) {
      if ($depth == 0) {
        $carry = $tr .$td . $key;
        show_attr($attrs[$key], $result,$depth + 1, $carry, $tr, $td);
      } else{
        show_attr($attrs[$key], $result,$depth + 1, $carry . '.' . $key , $tr, $td);
      }
    }else{
      if ($depth == 0){
        $result .= $tr .$td . $key . '</td>'. $td . $value .'</td></tr>';
      } else{
        if (!empty($carry))
          $result .= $carry . '.' . $key . '</td>' . $td . $value .'</td></tr>';
      }
    }
  }
}
