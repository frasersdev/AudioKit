//
//  AKSoftClip.swift
//  AudioKit
//
//  Created by Fraser Stuart, revision history on Github.
//  Copyright © 2017 Fraser Stuart. All rights reserved.
//
//  Based on AKClipper.swift
//  Which was Created by Aurelius Prochazka
//  and is Copyright © 2017 Aurelius Prochazka. All rights reserved.
//

/// Clips a signal when it crosses -3db so that it never exceeds 0db in a manner similar to magnetic tape
///
open class AKSoftClip: AKNode, AKToggleable, AKComponent {
    public typealias AKAudioUnitType = AKClipperAudioUnit
    /// Four letter unique description of the node
    public static let ComponentDescription = AudioComponentDescription(effect: "sclp")

    // MARK: - Properties

    private var internalAU: AKAudioUnitType?
    private var token: AUParameterObserverToken?

    /// Ramp Time represents the speed at which parameters are allowed to change
    open dynamic var rampTime: Double = AKSettings.rampTime {
        willSet {
            internalAU?.rampTime = newValue
        }
    }


    /// Tells whether the node is processing (ie. started, playing, or active)
    open dynamic var isStarted: Bool {
        return internalAU?.isPlaying() ?? false
    }

    // MARK: - Initialization

    /// Initialize this clipper node
    ///
    /// - Parameters:
    ///   - input: Input node to process
    ///
    public init(
        _ input: AKNode?) {

        _Self.register()

        super.init()
        AVAudioUnit._instantiate(with: _Self.ComponentDescription) { [weak self] in
            self?.avAudioNode = $0
            self?.internalAU = $0.auAudioUnit as? AKAudioUnitType

            input?.addConnectionPoint(self!)
        }
    }

    // MARK: - Control

    /// Function to start, play, or activate the node, all do the same thing
    open func start() {
        internalAU?.start()
    }

    /// Function to stop or bypass the node, both are equivalent
    open func stop() {
        internalAU?.stop()
    }
}
