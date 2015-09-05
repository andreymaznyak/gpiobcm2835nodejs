{
  'targets': [
    {
      'target_name': 'gpiobcm2835nodejs',
      'sources': [
        'src/gpiobcm2835nodejs.cc',
      ],
      "cflags" : [ "-lrt -lbcm2835" ]
    }
  ]
}