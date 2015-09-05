{
  'targets': [
    {
      'target_name': 'gpiobcm2835nodejs',
      'sources': [
        'src/gpiobcm2835nodejs.cc',
        'src/gpio_functions.cc'
      ],
      "cflags" : [ "-lrt -lbcm2835" ],
      'conditions': [
                ['OS=="linux"', {
                  'cflags!': [
                    '-lrt -lbcm2835',
                  ],
                }],
              ]
    }
  ]
}