{
  'targets': [
    {
      'target_name': 'md5-nan',
      'include_dirs': [
        "<!(node -e \"require('nan')\")"
      ],
      'sources': [
        'src/init.cc'
      ]
    }
  ]
}
