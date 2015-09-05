{
  'targets': [
    {
      'target_name': 'gpiobcm2835nodejs',
      'sources': [
        'src/gpiobcm2835nodejs.cc',
      ],
      'conditions': [
        ['OS=="linux"', {
          'cflags': [
            '<!@(pkg-config --cflags gpiobcm2835nodejs)'
          ],
          'ldflags': [
            '<!@(pkg-config --libs-only-L --libs-only-other gpiobcm2835nodejs)'
          ],
          'libraries': [
            '<!@(pkg-config --libs-only-l gpiobcm2835nodejs)'
          ]
        }]
      ]
    }
  ]
}